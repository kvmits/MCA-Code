<?php

require_once __DIR__ . "/common.php";
apiStartSession();

if ($_SERVER["REQUEST_METHOD"] === "GET") {
    if (($_GET["action"] ?? "") !== "session") {
        apiRespond(400, ["success" => false, "error" => "Unknown action."]);
    }

    $token = apiAccessToken();
    $user = $token ? apiCurrentUser() : null;
    apiRespond(200, [
        "success" => true,
        "authenticated" => $user !== null,
        "user" => $user ? [
            "email" => $user["email"],
            "displayName" => $user["display_name"],
        ] : null,
    ]);
}

if ($_SERVER["REQUEST_METHOD"] !== "POST") {
    header("Allow: GET, POST");
    apiRespond(405, ["success" => false, "error" => "Method not allowed."]);
}

$payload = apiReadJson();
$action = $payload["action"] ?? "";

if ($action === "logout") {
    apiDestroySession();
    apiRespond(200, ["success" => true]);
}

if ($action === "confirm") {
    $accessToken = $payload["accessToken"] ?? "";
    $refreshToken = $payload["refreshToken"] ?? "";
    $expiresIn = filter_var($payload["expiresIn"] ?? 3600, FILTER_VALIDATE_INT);
    if (!is_string($accessToken) || strlen($accessToken) < 20 || strlen($accessToken) > 8192
        || !is_string($refreshToken) || strlen($refreshToken) < 20 || strlen($refreshToken) > 8192
        || $expiresIn === false || $expiresIn < 60 || $expiresIn > 86400) {
        apiRespond(400, ["success" => false, "error" => "That confirmation link is incomplete or invalid. Request a new one and try again."]);
    }

    $verified = supabaseAuthRequest("user", "GET", null, $accessToken);
    if (!$verified["success"] || empty($verified["data"]["id"])) {
        apiRespond(401, ["success" => false, "error" => "That confirmation link has expired or was already used. Request a new one and try again."]);
    }

    if (!apiStoreAuthSession([
        "access_token" => $accessToken,
        "refresh_token" => $refreshToken,
        "expires_in" => $expiresIn,
        "user" => $verified["data"],
    ])) {
        apiRespond(502, ["success" => false, "error" => "Your email was confirmed, but Campify could not start a session. Please sign in."]);
    }
    apiRespond(200, ["success" => true]);
}

if ($action === "change-password" || $action === "delete-account") {
    $currentUser = apiCurrentUser();
    if (!$currentUser || empty($currentUser["email"]) || empty($currentUser["id"])) {
        apiRespond(401, ["success" => false, "error" => "Sign in again before changing your account."]);
    }

    $currentPassword = (string) ($payload["currentPassword"] ?? "");
    if (strlen($currentPassword) < 8 || strlen($currentPassword) > 128) {
        apiRespond(400, ["success" => false, "error" => "Enter your current password."]);
    }

    $verified = supabaseAuthRequest("token?grant_type=password", "POST", [
        "email" => $currentUser["email"],
        "password" => $currentPassword,
    ]);
    if (!$verified["success"]) {
        if (isset($verified["error"]) || ($verified["status"] ?? 0) >= 500 || ($verified["status"] ?? 0) === 429) {
            apiRespond(502, ["success" => false, "error" => "Could not verify your password right now. Try again shortly."]);
        }
        apiRespond(401, ["success" => false, "error" => "Your current password is incorrect."]);
    }
    if (($verified["data"]["user"]["id"] ?? "") !== $currentUser["id"]) {
        apiRespond(401, ["success" => false, "error" => "The signed-in account could not be verified. Sign in again."]);
    }

    if ($action === "change-password") {
        $newPassword = (string) ($payload["newPassword"] ?? "");
        $confirmPassword = (string) ($payload["confirmPassword"] ?? "");
        if (strlen($newPassword) < 8 || strlen($newPassword) > 128) {
            apiRespond(400, ["success" => false, "error" => "Your new password must be between 8 and 128 characters."]);
        }
        if ($newPassword !== $confirmPassword) {
            apiRespond(400, ["success" => false, "error" => "Your new passwords do not match."]);
        }
        if ($newPassword === $currentPassword) {
            apiRespond(400, ["success" => false, "error" => "Choose a new password that is different from your current one."]);
        }

        $updated = supabaseAuthRequest("user", "PUT", [
            "password" => $newPassword,
        ], $verified["data"]["access_token"]);
        if (!$updated["success"]) {
            apiRespond(502, ["success" => false, "error" => "Your password could not be updated. Try again shortly."]);
        }
        apiRespond(200, ["success" => true]);
    }

    if (($payload["confirmed"] ?? false) !== true) {
        apiRespond(400, ["success" => false, "error" => "Confirm that you understand your account and listings will be permanently deleted."]);
    }

    $deleted = supabaseRequest(
        "rpc/delete_own_account",
        "POST",
        new stdClass(),
        $verified["data"]["access_token"]
    );
    if (!$deleted["success"]) {
        if (($deleted["data"]["code"] ?? "") === "PGRST202") {
            apiRespond(502, ["success" => false, "error" => "Account deletion is not set up yet. Run the latest schema.sql in the Supabase SQL Editor."]);
        }
        apiRespond(502, ["success" => false, "error" => "Your account could not be deleted. Try again shortly."]);
    }

    apiDestroySession();
    apiRespond(200, ["success" => true]);
}

$email = strtolower(trim((string) ($payload["email"] ?? "")));
$password = (string) ($payload["password"] ?? "");
if (!filter_var($email, FILTER_VALIDATE_EMAIL)
    || !preg_match('/^[^\s@]+@mgits\.ac\.in$/i', $email)
    || strlen($password) < 8
    || strlen($password) > 128) {
    apiRespond(400, ["success" => false, "error" => "Use a valid @mgits.ac.in email and a password between 8 and 128 characters."]);
}

if ($action === "register") {
    $displayName = trim((string) ($payload["displayName"] ?? ""));
    if (mb_strlen($displayName) < 2 || mb_strlen($displayName) > 40) {
        apiRespond(400, ["success" => false, "error" => "Your display name must be between 2 and 40 characters."]);
    }

    global $siteUrl;
    $redirectUrl = rtrim($siteUrl, "/") . "/auth-confirmation.html";
    $result = supabaseAuthRequest("signup?redirect_to=" . rawurlencode($redirectUrl), "POST", [
        "email" => $email,
        "password" => $password,
        "data" => ["display_name" => $displayName],
    ]);

    if (!$result["success"]) {
        $failure = apiSignupFailure($result);
        apiRespond($failure["status"], ["success" => false, "error" => $failure["error"]]);
    }

    if (apiStoreAuthSession($result["data"], $displayName)) {
        apiRespond(201, ["success" => true, "authenticated" => true]);
    }

    apiRespond(200, [
        "success" => true,
        "authenticated" => false,
        "confirmationRequired" => true,
        "message" => "Check your college email for a confirmation link, then sign in.",
    ]);
}

if ($action === "login") {
    $result = supabaseAuthRequest("token?grant_type=password", "POST", [
        "email" => $email,
        "password" => $password,
    ]);

    if (!$result["success"]) {
        if (isset($result["error"]) || ($result["status"] ?? 0) >= 500 || ($result["status"] ?? 0) === 429) {
            apiRespond(502, ["success" => false, "error" => "Authentication service is unavailable. Try again shortly."]);
        }
        apiRespond(401, ["success" => false, "error" => "That email and password don't match, or the account needs email confirmation."]);
    }
    if (!apiStoreAuthSession($result["data"] ?? [])) {
        apiRespond(502, ["success" => false, "error" => "Authentication service returned an invalid session. Try again shortly."]);
    }

    apiRespond(200, ["success" => true, "authenticated" => true]);
}

apiRespond(400, ["success" => false, "error" => "Unknown action."]);

?>

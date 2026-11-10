<?php

require_once dirname(__DIR__) . "/db.php";

function apiRespond($status, $payload)
{
    http_response_code($status);
    header("Content-Type: application/json; charset=utf-8");
    echo json_encode($payload);
    exit;
}

function apiStartSession()
{
    ini_set("session.use_strict_mode", "1");
    session_name("campify_session");
    session_set_cookie_params([
        "lifetime" => 0,
        "path" => "/",
        "secure" => !empty($_SERVER["HTTPS"]) && $_SERVER["HTTPS"] !== "off",
        "httponly" => true,
        "samesite" => "Lax",
    ]);
    session_start();
}

function apiReadJson()
{
    $body = file_get_contents("php://input");
    $payload = json_decode($body, true);
    if (!is_array($payload) || json_last_error() !== JSON_ERROR_NONE) {
        apiRespond(400, ["success" => false, "error" => "Send a valid JSON request."]);
    }
    return $payload;
}

function apiDestroySession()
{
    $_SESSION = [];
    $cookie = session_get_cookie_params();
    setcookie(session_name(), "", [
        "expires" => time() - 42000,
        "path" => $cookie["path"],
        "domain" => $cookie["domain"],
        "secure" => $cookie["secure"],
        "httponly" => $cookie["httponly"],
        "samesite" => $cookie["samesite"],
    ]);
    session_destroy();
}

function apiAccessToken()
{
    if (empty($_SESSION["access_token"])) {
        return null;
    }

    if ((int) ($_SESSION["expires_at"] ?? 0) <= time() + 60) {
        if (empty($_SESSION["refresh_token"])) {
            apiDestroySession();
            return null;
        }

        $refreshed = supabaseAuthRequest("token?grant_type=refresh_token", "POST", [
            "refresh_token" => $_SESSION["refresh_token"],
        ]);
        if (!$refreshed["success"] || empty($refreshed["data"]["access_token"])) {
            apiDestroySession();
            return null;
        }

        $_SESSION["access_token"] = $refreshed["data"]["access_token"];
        $_SESSION["refresh_token"] = $refreshed["data"]["refresh_token"] ?? $_SESSION["refresh_token"];
        $_SESSION["expires_at"] = time() + (int) ($refreshed["data"]["expires_in"] ?? 3600);
    }

    return $_SESSION["access_token"];
}

function apiStoreAuthSession($authData, $fallbackName = "")
{
    if (empty($authData["access_token"]) || empty($authData["user"]["id"])) {
        return false;
    }

    session_regenerate_id(true);
    $user = $authData["user"];
    $metadata = $user["user_metadata"] ?? [];
    $displayName = trim((string) ($metadata["display_name"] ?? $fallbackName));
    if ($displayName === "") {
        $displayName = explode("@", (string) ($user["email"] ?? ""))[0];
    }
    $displayName = mb_substr($displayName, 0, 40);
    if (mb_strlen($displayName) < 2) {
        $displayName = "Student";
    }
    $_SESSION["access_token"] = $authData["access_token"];
    $_SESSION["refresh_token"] = $authData["refresh_token"] ?? "";
    $_SESSION["expires_at"] = time() + (int) ($authData["expires_in"] ?? 3600);
    $_SESSION["user"] = [
        "id" => $user["id"],
        "email" => $user["email"] ?? "",
        "display_name" => $displayName,
    ];
    return true;
}

function apiCurrentUser()
{
    return $_SESSION["user"] ?? null;
}

function apiSignupFailure($result)
{
    $providerMessage = strtolower(trim((string) (
        $result["data"]["msg"]
        ?? $result["data"]["message"]
        ?? $result["data"]["error_description"]
        ?? $result["error"]
        ?? ""
    )));
    $providerCode = strtolower(trim((string) (
        $result["data"]["code"]
        ?? $result["data"]["error_code"]
        ?? ""
    )));
    $details = $providerCode . " " . $providerMessage;

    if (strpos($details, "already registered") !== false
        || strpos($details, "already been registered") !== false
        || strpos($details, "email_exists") !== false) {
        return [
            "status" => 409,
            "error" => "That college email already has an account. Sign in, or use password reset if you forgot the password.",
        ];
    }
    if (strpos($details, "email address not authorized") !== false
        || strpos($details, "email_not_authorized") !== false) {
        return [
            "status" => 502,
            "error" => "Supabase's default email service can only send to project team addresses. Configure custom SMTP in Supabase Auth → SMTP Settings, then try again.",
        ];
    }
    if (strpos($details, "redirect url") !== false
        || strpos($details, "redirect_to") !== false
        || strpos($details, "redirect uri") !== false) {
        return [
            "status" => 502,
            "error" => "Supabase rejected the confirmation redirect. Add http://localhost:8000/auth-confirmation.html under Authentication → URL Configuration → Redirect URLs.",
        ];
    }
    if (strpos($details, "rate limit") !== false || ($result["status"] ?? 0) === 429) {
        return [
            "status" => 429,
            "error" => "Supabase's email limit was reached. Wait before trying again, or configure custom SMTP in Supabase Auth → SMTP Settings.",
        ];
    }
    if (strpos($details, "password") !== false && strpos($details, "weak") !== false) {
        return [
            "status" => 400,
            "error" => "Supabase rejected this password. Choose a stronger password and try again.",
        ];
    }

    $status = (int) ($result["status"] ?? 0);
    if ($status === 0) {
        return [
            "status" => 502,
            "error" => "Could not reach Supabase Auth. Check the connection and try again.",
        ];
    }
    return [
        "status" => 502,
        "error" => "Supabase rejected signup (HTTP " . $status . "). Check Authentication → Logs in Supabase for the exact provider error.",
    ];
}

?>

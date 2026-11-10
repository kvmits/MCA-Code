<?php

require_once __DIR__ . "/common.php";
apiStartSession();
$accessToken = apiAccessToken();
if (!$accessToken) {
    apiRespond(401, ["success" => false, "error" => "Sign in to manage saved listings."]);
}

$user = apiCurrentUser();
if ($_SERVER["REQUEST_METHOD"] === "GET") {
    $result = supabaseRequest(
        "listing_favorites?select=listing_id&owner_id=eq." . rawurlencode($user["id"]),
        "GET",
        null,
        $accessToken
    );
    if (!$result["success"] || !is_array($result["data"])) {
        apiRespond(502, ["success" => false, "error" => "Could not load your saved listings."]);
    }

    apiRespond(200, [
        "success" => true,
        "listingIds" => array_column($result["data"], "listing_id"),
    ]);
}

if ($_SERVER["REQUEST_METHOD"] !== "POST") {
    header("Allow: GET, POST");
    apiRespond(405, ["success" => false, "error" => "Method not allowed."]);
}

$payload = apiReadJson();
$action = $payload["action"] ?? "";
$listingId = $payload["listingId"] ?? "";
if (!is_string($listingId)
    || !preg_match('/^[0-9a-f]{8}-[0-9a-f]{4}-[1-8][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i', $listingId)
    || !in_array($action, ["save", "remove"], true)) {
    apiRespond(400, ["success" => false, "error" => "Choose a valid listing and action."]);
}

if ($action === "save") {
    $result = supabaseRequest(
        "listing_favorites?on_conflict=owner_id%2Clisting_id",
        "POST",
        ["owner_id" => $user["id"], "listing_id" => $listingId],
        $accessToken,
        "resolution=ignore-duplicates"
    );
} else {
    $result = supabaseRequest(
        "listing_favorites?owner_id=eq." . rawurlencode($user["id"]) . "&listing_id=eq." . rawurlencode($listingId),
        "DELETE",
        null,
        $accessToken
    );
}

if (!$result["success"]) {
    apiRespond(502, ["success" => false, "error" => "Could not update your saved listings."]);
}

apiRespond(200, ["success" => true]);

?>

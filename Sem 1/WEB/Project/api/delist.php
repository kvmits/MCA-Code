<?php

require_once __DIR__ . "/common.php";
apiStartSession();
$accessToken = apiAccessToken();
if (!$accessToken) {
    apiRespond(401, ["success" => false, "error" => "Sign in to delist your post."]);
}

if ($_SERVER["REQUEST_METHOD"] !== "POST") {
    header("Allow: POST");
    apiRespond(405, ["success" => false, "error" => "Method not allowed."]);
}

$payload = apiReadJson();
$listingId = $payload["listingId"] ?? "";
if (!is_string($listingId)
    || !preg_match('/^[0-9a-f]{8}-[0-9a-f]{4}-[1-8][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i', $listingId)) {
    apiRespond(400, ["success" => false, "error" => "Choose a valid post to delist."]);
}

$user = apiCurrentUser();
$result = supabaseRequest(
    "listings?id=eq." . rawurlencode($listingId)
        . "&owner_id=eq." . rawurlencode($user["id"])
        . "&delisted_at=is.null",
    "PATCH",
    ["delisted_at" => gmdate("Y-m-d\TH:i:s\Z")],
    $accessToken,
    "return=representation"
);

if (!$result["success"]) {
    if (in_array($result["data"]["code"] ?? "", ["42703", "PGRST204"], true)) {
        apiRespond(502, ["success" => false, "error" => "Delisting is not set up yet. Run the updated schema.sql in the Supabase SQL Editor."]);
    }
    apiRespond(502, ["success" => false, "error" => "Could not delist this post. Check the database setup and try again."]);
}

if (empty($result["data"][0]["id"])) {
    apiRespond(404, ["success" => false, "error" => "This post was not found or has already been delisted."]);
}

apiRespond(200, [
    "success" => true,
    "delistedAt" => $result["data"][0]["delisted_at"],
]);

?>

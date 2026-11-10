<?php

require_once __DIR__ . "/common.php";
apiStartSession();
$accessToken = apiAccessToken();
if (!$accessToken) {
    apiRespond(401, ["success" => false, "error" => "Sign in to view your profile."]);
}

if ($_SERVER["REQUEST_METHOD"] !== "GET") {
    header("Allow: GET");
    apiRespond(405, ["success" => false, "error" => "Method not allowed."]);
}

$user = apiCurrentUser();
$result = supabaseRequest(
    "listings?select=id,kind,direction,title,description,price,category,emoji,tag,image_url,created_at,delisted_at&owner_id=eq." . rawurlencode($user["id"]) . "&order=created_at.desc",
    "GET",
    null,
    $accessToken
);
if (!$result["success"] || !is_array($result["data"])) {
    if (in_array($result["data"]["code"] ?? "", ["42703", "PGRST204"], true)) {
        apiRespond(502, ["success" => false, "error" => "Delisting is not set up yet. Run the updated schema.sql in the Supabase SQL Editor, then refresh your profile."]);
    }
    apiRespond(502, ["success" => false, "error" => "Could not load your listings. Check the Supabase schema and try again."]);
}

$listings = array_map(function ($listing) {
    return [
        "id" => $listing["id"],
        "kind" => $listing["kind"],
        "direction" => $listing["direction"],
        "title" => $listing["title"],
        "description" => $listing["description"],
        "price" => $listing["price"],
        "category" => $listing["category"],
        "emoji" => $listing["emoji"],
        "tag" => $listing["tag"],
        "image" => $listing["image_url"],
        "createdAt" => $listing["created_at"],
        "delistedAt" => $listing["delisted_at"],
    ];
}, $result["data"]);

apiRespond(200, [
    "success" => true,
    "email" => $user["email"],
    "displayName" => $user["display_name"],
    "listings" => $listings,
]);

?>

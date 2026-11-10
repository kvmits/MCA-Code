<?php

require_once __DIR__ . "/common.php";
apiStartSession();

function listingDatabaseError($result)
{
    $code = $result["data"]["code"] ?? "";
    if ($code === "42703" || $code === "PGRST204") {
        return "Listing status is not set up yet. Run the updated schema.sql in the Supabase SQL Editor, then try again.";
    }
    if ($code === "PGRST205") {
        return "The listings table is missing. Run schema.sql in your Supabase SQL Editor, then try again.";
    }
    if ($code === "42501") {
        return "Supabase denied access to listings. Check that the listings RLS policies from schema.sql are installed.";
    }
    return "Could not access listings in Supabase. Check the database setup and try again.";
}

$accessToken = apiAccessToken();
if (!$accessToken) {
    apiRespond(401, ["success" => false, "error" => "Sign in to view campus listings."]);
}

if ($_SERVER["REQUEST_METHOD"] === "GET") {
    $result = supabaseRequest(
        "listings?select=id,kind,direction,title,description,price,category,seller_name,contact_email,emoji,tag,image_url,created_at&delisted_at=is.null&order=created_at.desc",
        "GET",
        null,
        $accessToken
    );
    if (!$result["success"] || !is_array($result["data"])) {
        apiRespond(502, ["success" => false, "error" => listingDatabaseError($result)]);
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
            "seller" => $listing["seller_name"],
            "email" => $listing["contact_email"],
            "initial" => mb_strtoupper(mb_substr($listing["seller_name"], 0, 1)),
            "emoji" => $listing["emoji"],
            "tag" => $listing["tag"],
            "image" => $listing["image_url"],
            "createdAt" => $listing["created_at"],
        ];
    }, $result["data"]);

    apiRespond(200, ["success" => true, "listings" => $listings]);
}

if ($_SERVER["REQUEST_METHOD"] !== "POST") {
    header("Allow: GET, POST");
    apiRespond(405, ["success" => false, "error" => "Method not allowed."]);
}

$payload = apiReadJson();
$kind = $payload["kind"] ?? "";
$direction = $payload["direction"] ?? null;
$title = trim((string) ($payload["title"] ?? ""));
$description = trim((string) ($payload["description"] ?? ""));
$category = $payload["category"] ?? "";
$price = $payload["price"] ?? null;
$image = $payload["image"] ?? null;
$categories = ["books", "tech", "living", "style", "help", "other"];
$user = apiCurrentUser();

if (!in_array($kind, ["item", "gig"], true)
    || ($kind === "gig" && !in_array($direction, ["offer", "request"], true))
    || ($kind === "item" && $direction !== null)
    || !in_array($category, $categories, true)
    || ($kind === "item" && $category === "help")
    || !is_numeric($price)
    || (float) $price < 0
    || (float) $price > 9999999
    || mb_strlen($title) < 3
    || mb_strlen($title) > 60
    || mb_strlen($description) < 3
    || mb_strlen($description) > 240) {
    apiRespond(400, ["success" => false, "error" => "Check the listing details and try again."]);
}

if ($kind === "gig") {
    $category = "help";
}

if ($image !== null && (!is_string($image)
    || strlen($image) > 1400000
    || !preg_match('/\Adata:image\/(?:png|jpeg|webp|gif);base64,[A-Za-z0-9+\/]+=*\z/', $image))) {
    apiRespond(400, ["success" => false, "error" => "Choose a PNG, JPEG, GIF, or WebP image under 1 MB."]);
}

$result = supabaseRequest("listings", "POST", [
    "owner_id" => $user["id"],
    "contact_email" => $user["email"],
    "kind" => $kind,
    "direction" => $kind === "gig" ? $direction : null,
    "title" => $title,
    "description" => $description,
    "price" => (float) $price,
    "category" => $category,
    "seller_name" => $user["display_name"],
    "emoji" => $kind === "gig" ? "✳" : "📦",
    "tag" => $kind === "gig" ? ($direction === "request" ? "HELP WANTED" : "STUDENT HELP") : "JUST LISTED",
    "image_url" => $image,
], $accessToken);

if (!$result["success"]) {
    apiRespond(502, ["success" => false, "error" => listingDatabaseError($result)]);
}

apiRespond(201, ["success" => true]);

?>

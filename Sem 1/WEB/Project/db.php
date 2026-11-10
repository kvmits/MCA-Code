<?php

$url = "https://cwzmdcwxtewkuvtexmbm.supabase.co";
$apiKey = "sb_publishable_KRiLtP-7hiHSjkZY_jubJg_IRMogCAz";
$siteUrl = getenv("CAMPIFY_SITE_URL") ?: "http://localhost:8000";

function supabaseHttpRequest($path, $method = "GET", $data = null, $accessToken = null, $prefer = null)
{
    global $url, $apiKey;

    $ch = curl_init(rtrim($url, "/") . $path);
    $headers = [
        "apikey: " . $apiKey,
        "Authorization: Bearer " . ($accessToken ?: $apiKey),
        "Content-Type: application/json",
    ];
    if ($prefer !== null) {
        $headers[] = "Prefer: " . $prefer;
    }

    curl_setopt_array($ch, [
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_HTTPHEADER => $headers,
        CURLOPT_CUSTOMREQUEST => $method,
        CURLOPT_CONNECTTIMEOUT => 8,
        CURLOPT_TIMEOUT => 20,
    ]);

    if ($data !== null) {
        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    }

    $response = curl_exec($ch);
    if ($response === false) {
        $error = curl_error($ch);
        curl_close($ch);
        return ["success" => false, "error" => $error];
    }

    $statusCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);

    return [
        "success" => $statusCode >= 200 && $statusCode < 300,
        "status" => $statusCode,
        "data" => json_decode($response, true),
    ];
}

function supabaseRequest($endpoint, $method = "GET", $data = null, $accessToken = null, $prefer = null)
{
    return supabaseHttpRequest("/rest/v1/" . ltrim($endpoint, "/"), $method, $data, $accessToken, $prefer);
}

function supabaseAuthRequest($endpoint, $method = "POST", $data = null, $accessToken = null)
{
    return supabaseHttpRequest("/auth/v1/" . ltrim($endpoint, "/"), $method, $data, $accessToken);
}

?>

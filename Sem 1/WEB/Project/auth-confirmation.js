const title = document.querySelector("#confirmation-title");
const message = document.querySelector("#confirmation-message");
const loginLink = document.querySelector("#confirmation-login");
const params = new URLSearchParams(window.location.hash.slice(1));
const accessToken = params.get("access_token");
const refreshToken = params.get("refresh_token");
const expiresIn = Number(params.get("expires_in") || 3600);
const confirmationType = params.get("type");

function showFailure(error) {
  title.textContent = "Confirmation link issue";
  message.textContent = error;
  loginLink.hidden = false;
}

if (params.get("error")) {
  showFailure(params.get("error_description") || "This confirmation link is no longer valid. Request a new confirmation email.");
} else if (!accessToken || !refreshToken || confirmationType !== "signup") {
  showFailure("This confirmation link is incomplete or invalid. Request a new confirmation email.");
} else {
  fetch("api/auth.php", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ action: "confirm", accessToken, refreshToken, expiresIn }),
  })
    .then(async (response) => {
      const result = await response.json();
      if (!response.ok) throw new Error(result.error || "Could not confirm your email.");
      window.history.replaceState(null, "", window.location.pathname);
      title.textContent = "Email confirmed!";
      message.textContent = "Your account is ready. Taking you to the campus marketplace…";
      window.setTimeout(() => window.location.replace("index.html"), 1200);
    })
    .catch((error) => showFailure(error.message || "Could not reach Campify. Please try the link again."));
}

const loginForm = document.querySelector("#login-form");
const loginError = document.querySelector("#login-error");
const collegeEmailInput = document.querySelector("#login-email");
const displayNameField = document.querySelector("#display-name-field");
const displayNameInput = document.querySelector("#login-display-name");
const confirmPasswordField = document.querySelector("#confirm-password-field");
const confirmPasswordInput = document.querySelector("#login-confirm-password");
const submitLabel = document.querySelector("#submit-label");
const authTabs = document.querySelectorAll("[data-auth-mode]");
let authMode = "login";

if (new URLSearchParams(window.location.search).get("notice") === "account-deleted") {
  showSuccess("Your account and listings have been deleted.");
}

fetch("api/auth.php?action=session")
  .then((response) => response.json())
  .then((result) => {
    if (result.authenticated) window.location.replace("index.html");
  })
  .catch(() => showError("Could not check your sign-in session. Make sure PHP is running."));

function showError(message) {
  loginError.textContent = message;
  loginError.classList.remove("success");
  loginError.hidden = false;
}

function showSuccess(message) {
  loginError.textContent = message;
  loginError.classList.add("success");
  loginError.hidden = false;
}

function setAuthMode(mode) {
  authMode = mode;
  const isRegistering = mode === "register";
  displayNameField.hidden = !isRegistering;
  displayNameInput.required = isRegistering;
  confirmPasswordField.hidden = !isRegistering;
  confirmPasswordInput.required = isRegistering;
  document.querySelector("#login-password").autocomplete = isRegistering ? "new-password" : "current-password";
  submitLabel.textContent = isRegistering ? "Create account" : "Sign in";
  document.querySelector("#login-title").textContent = isRegistering ? "Make yourself at home." : "Let's get you in.";
  document.querySelector(".login-intro").textContent = isRegistering
    ? "Create an account to join your campus marketplace."
    : "Sign in to explore your campus marketplace.";
  loginError.hidden = true;
  authTabs.forEach((tab) => {
    const isActive = tab.dataset.authMode === mode;
    tab.classList.toggle("active", isActive);
    tab.setAttribute("aria-selected", String(isActive));
  });
}

authTabs.forEach((tab) => tab.addEventListener("click", () => setAuthMode(tab.dataset.authMode)));

loginForm.addEventListener("submit", async (event) => {
  event.preventDefault();
  const email = collegeEmailInput.value.trim().toLowerCase();
  const displayName = displayNameInput.value.trim();
  const password = document.querySelector("#login-password").value;
  if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email)) {
    showError("Enter a valid email address.");
    collegeEmailInput.focus();
    return;
  }
  if (authMode === "register" && !/^[^\s@]+@mgits\.ac\.in$/i.test(email)) {
    showError("Use a valid college email ending with @mgits.ac.in.");
    collegeEmailInput.focus();
    return;
  }
  if (authMode === "register" && (displayName.length < 2 || displayName.length > 40)) {
    showError("Your display name must be between 2 and 40 characters.");
    displayNameInput.focus();
    return;
  }
  if (password.length < 8) {
    showError("Your password must be at least 8 characters.");
    document.querySelector("#login-password").focus();
    return;
  }
  if (authMode === "register" && password !== confirmPasswordInput.value) {
    showError("Those passwords do not match.");
    confirmPasswordInput.focus();
    return;
  }

  const submitButton = loginForm.querySelector('button[type="submit"]');
  submitButton.disabled = true;
  submitLabel.textContent = "Please wait...";
  try {
    const response = await fetch("api/auth.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        action: authMode,
        email,
        password,
        ...(authMode === "register" ? { displayName } : {}),
      }),
    });
    const result = await response.json();
    if (!response.ok) {
      showError(result.error || "Authentication failed. Try again.");
      return;
    }
    if (result.confirmationRequired) {
      window.location.assign(`check-email.html?message=${encodeURIComponent(result.message)}`);
      return;
    }
    window.location.replace("index.html");
  } catch (error) {
    showError("Could not reach Campify. Run the site through PHP/Apache and try again.");
  } finally {
    submitButton.disabled = false;
    submitLabel.textContent = authMode === "register" ? "Create account" : "Sign in";
  }
});

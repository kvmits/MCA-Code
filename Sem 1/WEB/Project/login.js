const accountStorageKey = "campify-accounts-v1";
const authStorageKey = "campify-auth-session-v1";
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

try {
  if (sessionStorage.getItem(authStorageKey)) {
    window.location.replace("index.html");
  }
} catch (error) {
  console.warn("Campify could not read the login session.", error);
}

function readAccounts() {
  try {
    const accounts = JSON.parse(localStorage.getItem(accountStorageKey) || "[]");
    return Array.isArray(accounts) ? accounts : [];
  } catch (error) {
    console.warn("Campify could not read local accounts.", error);
    return [];
  }
}

function bytesToBase64(bytes) {
  return btoa(String.fromCharCode(...bytes));
}

function base64ToBytes(value) {
  return Uint8Array.from(atob(value), (character) => character.charCodeAt(0));
}

async function derivePasswordHash(password, salt) {
  const passwordKey = await crypto.subtle.importKey(
    "raw",
    new TextEncoder().encode(password),
    "PBKDF2",
    false,
    ["deriveBits"],
  );
  const derivedBits = await crypto.subtle.deriveBits(
    { name: "PBKDF2", salt: base64ToBytes(salt), iterations: 100000, hash: "SHA-256" },
    passwordKey,
    256,
  );
  return bytesToBase64(new Uint8Array(derivedBits));
}

function createSalt() {
  const salt = new Uint8Array(16);
  crypto.getRandomValues(salt);
  return bytesToBase64(salt);
}

function showError(message) {
  loginError.textContent = message;
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
  const confirmPassword = confirmPasswordInput.value;

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
  if (authMode === "register" && password !== confirmPassword) {
    showError("Those passwords do not match.");
    confirmPasswordInput.focus();
    return;
  }

  try {
    const accounts = readAccounts();
    const existingAccount = accounts.find((account) => account.email === email);

    if (authMode === "register") {
      if (existingAccount) {
        showError("That college email is already registered.");
        collegeEmailInput.focus();
        return;
      }
      const salt = createSalt();
      accounts.push({
        email,
        displayName,
        salt,
        passwordHash: await derivePasswordHash(password, salt),
      });
      localStorage.setItem(accountStorageKey, JSON.stringify(accounts));
    } else if (
      !existingAccount
      || !existingAccount.salt
      || existingAccount.passwordHash !== await derivePasswordHash(password, existingAccount.salt)
    ) {
      showError("That email and password don't match. Try again.");
      document.querySelector("#login-password").focus();
      return;
    }

    sessionStorage.setItem(authStorageKey, JSON.stringify({
      email,
      displayName: existingAccount?.displayName || displayName,
    }));
  } catch (error) {
    console.warn("Campify could not save the account or login session.", error);
    showError("Could not save your account in this browser. Check storage permissions and try again.");
    return;
  }
  window.location.replace("index.html");
});

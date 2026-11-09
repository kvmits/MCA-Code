const authStorageKey = "campify-demo-authenticated";
const loginForm = document.querySelector("#login-form");
const loginError = document.querySelector("#login-error");

try {
  if (sessionStorage.getItem(authStorageKey) === "true") {
    window.location.replace("index.html");
  }
} catch (error) {
  console.warn("Campify could not read the demo login session.", error);
}

loginForm.addEventListener("submit", (event) => {
  event.preventDefault();
  const username = document.querySelector("#login-username").value.trim();
  const password = document.querySelector("#login-password").value;
  if (username !== "admin" || password !== "admin") {
    loginError.hidden = false;
    document.querySelector("#login-password").focus();
    return;
  }

  try {
    sessionStorage.setItem(authStorageKey, "true");
  } catch (error) {
    console.warn("Campify could not save the demo login session.", error);
    loginError.textContent = "Could not start a login session in this browser.";
    loginError.hidden = false;
    return;
  }
  window.location.replace("index.html");
});

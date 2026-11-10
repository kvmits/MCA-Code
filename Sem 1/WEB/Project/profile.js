const profileEmail = document.querySelector("#profile-email");
const listingsContainer = document.querySelector("#profile-listings");
const emptyListings = document.querySelector("#profile-listings-empty");
const toast = document.querySelector("#profile-toast");
const profileTabs = document.querySelectorAll("[data-profile-tab]");
let toastTimer;

function escapeHTML(value) {
  return String(value).replace(/[&<>"']/g, (character) => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;",
  })[character]);
}

function formatPrice(price) {
  return Number(price) === 0 ? "Free" : `₹${Number(price).toLocaleString("en-IN")}`;
}

function formatDelistedDate(value) {
  const date = new Date(value);
  if (Number.isNaN(date.getTime())) return "Date unavailable";
  return date.toLocaleString(undefined, {
    year: "numeric",
    month: "short",
    day: "numeric",
    hour: "numeric",
    minute: "2-digit",
  });
}

function showMessage(element, text, success = false) {
  element.textContent = text;
  element.classList.toggle("success", success);
  element.hidden = false;
}

function showToast(message) {
  toast.textContent = message;
  toast.classList.add("visible");
  window.clearTimeout(toastTimer);
  toastTimer = window.setTimeout(() => toast.classList.remove("visible"), 3200);
}

function renderListings(listings) {
  listingsContainer.innerHTML = listings.map((listing) => {
    const title = escapeHTML(listing.title);
    const category = escapeHTML(listing.category);
    const delisted = Boolean(listing.delistedAt);
    const image = listing.image
      ? `<img src="${escapeHTML(listing.image)}" alt="${title}" class="profile-listing-image"><span class="profile-listing-placeholder ${category}" aria-hidden="true">${escapeHTML(listing.emoji || "✳")}</span>`
      : `<span class="profile-listing-placeholder ${category}" aria-hidden="true">${escapeHTML(listing.emoji || "✳")}</span>`;
    const type = listing.kind === "gig"
      ? listing.direction === "request" ? "Student help · Looking for help" : "Student help · Offering a skill"
      : "For sale";
    return `<article class="profile-listing-card${delisted ? " delisted" : ""}">
      <div class="profile-listing-art">${image}<span class="item-tag">${escapeHTML(listing.tag || type)}</span></div>
      <div class="profile-listing-content">
        <span class="profile-listing-type">${escapeHTML(type)} · ${category}</span>
        <div class="profile-listing-title-row"><h3>${title}</h3><span>${formatPrice(listing.price)}</span></div>
        <p>${escapeHTML(listing.description)}</p>
        ${delisted
          ? `<span class="delisted-date">Delisted ${escapeHTML(formatDelistedDate(listing.delistedAt))}</span>`
          : `<button class="button button-danger profile-delist-button" type="button" data-delist="${escapeHTML(listing.id)}">Delist post</button>`}
      </div>
    </article>`;
  }).join("");

  listingsContainer.querySelectorAll(".profile-listing-image").forEach((image) => {
    image.addEventListener("error", () => image.classList.add("image-failed"), { once: true });
    image.addEventListener("load", () => {
      if (image.nextElementSibling) image.nextElementSibling.hidden = true;
    }, { once: true });
  });
  emptyListings.hidden = listings.length > 0;
  listingsContainer.hidden = listings.length === 0;
}

listingsContainer.addEventListener("click", async (event) => {
  const button = event.target.closest("[data-delist]");
  if (!button) return;
  const confirmed = window.confirm("Delist this post? It will disappear from the marketplace but stay in your profile.");
  if (!confirmed) return;

  button.disabled = true;
  try {
    const response = await fetch("api/delist.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ listingId: button.dataset.delist }),
    });
    const result = await response.json();
    if (!response.ok) throw new Error(result.error || "Could not delist this post.");

    const listingCard = button.closest(".profile-listing-card");
    const title = listingCard.querySelector(".profile-listing-title-row h3").textContent;
    const delistedLabel = document.createElement("span");
    delistedLabel.className = "delisted-date";
    delistedLabel.textContent = `Delisted ${formatDelistedDate(result.delistedAt)}`;
    button.replaceWith(delistedLabel);
    listingCard.classList.add("delisted");
    showToast(`“${title}” was delisted. It remains saved in your profile.`);
  } catch (error) {
    showToast(error.message || "Could not delist this post. Try again.");
    button.disabled = false;
  }
});

function setProfileTab(tabName) {
  profileTabs.forEach((tab) => {
    const active = tab.dataset.profileTab === tabName;
    tab.classList.toggle("active", active);
    tab.setAttribute("aria-selected", String(active));
  });
  document.querySelector("#my-listings-panel").hidden = tabName !== "listings";
  document.querySelector("#account-settings-panel").hidden = tabName !== "settings";
}

profileTabs.forEach((tab) => tab.addEventListener("click", () => setProfileTab(tab.dataset.profileTab)));

document.querySelector("#change-password-form").addEventListener("submit", async (event) => {
  event.preventDefault();
  const form = event.currentTarget;
  const data = new FormData(form);
  const message = document.querySelector("#password-message");
  message.hidden = true;
  const submitButton = form.querySelector('button[type="submit"]');
  submitButton.disabled = true;
  try {
    const response = await fetch("api/auth.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        action: "change-password",
        currentPassword: data.get("currentPassword"),
        newPassword: data.get("newPassword"),
        confirmPassword: data.get("confirmPassword"),
      }),
    });
    const result = await response.json();
    if (!response.ok) throw new Error(result.error || "Your password could not be changed.");
    form.reset();
    showMessage(message, "Your password has been updated.", true);
  } catch (error) {
    showMessage(message, error.message || "Could not reach Campify. Try again.");
  } finally {
    submitButton.disabled = false;
  }
});

document.querySelector("#delete-account-form").addEventListener("submit", async (event) => {
  event.preventDefault();
  const form = event.currentTarget;
  const data = new FormData(form);
  const message = document.querySelector("#delete-message");
  message.hidden = true;
  if (data.get("confirmed") !== "on") {
    showMessage(message, "Check the box to confirm permanent account deletion.");
    return;
  }

  const confirmed = window.confirm("Permanently delete your Campify account and all your listings? This cannot be undone.");
  if (!confirmed) return;

  const submitButton = form.querySelector('button[type="submit"]');
  submitButton.disabled = true;
  try {
    const response = await fetch("api/auth.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        action: "delete-account",
        currentPassword: data.get("currentPassword"),
        confirmed: true,
      }),
    });
    const result = await response.json();
    if (!response.ok) throw new Error(result.error || "Your account could not be deleted.");
    window.location.replace("login.html?notice=account-deleted");
  } catch (error) {
    showMessage(message, error.message || "Could not reach Campify. Try again.");
    submitButton.disabled = false;
  }
});

async function initializeProfile() {
  try {
    const response = await fetch("api/profile.php");
    const result = await response.json();
    if (!response.ok) {
      if (response.status === 401) {
        window.location.replace("login.html");
        return;
      }
      throw new Error(result.error || "Could not load your profile.");
    }

    profileEmail.textContent = result.email;
    renderListings(result.listings);
    document.body.hidden = false;
  } catch (error) {
    document.body.hidden = false;
    showToast(error.message || "Could not load your profile. Refresh and try again.");
  }
}

initializeProfile();

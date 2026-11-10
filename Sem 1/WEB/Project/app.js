let listings = [];
let savedIds = new Set();
let currentView = "items";
let currentCategory = "all";
let showAll = false;
let toastTimer;

const grid = document.querySelector("#listing-grid");
const searchInput = document.querySelector("#search-input");
const emptyState = document.querySelector("#empty-state");
const dialog = document.querySelector("#post-dialog");
const form = document.querySelector("#post-form");
const kindSelect = document.querySelector("#post-kind");
const directionSelect = document.querySelector("#post-direction");
const toast = document.querySelector("#toast");
const profileMenuButton = document.querySelector("[data-profile-menu]");
const profileDropdown = document.querySelector(".profile-dropdown");

async function logout() {
  try {
    const response = await fetch("api/auth.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ action: "logout" }),
    });
    if (!response.ok) throw new Error("The server could not end your session. Try again.");
    window.location.replace("login.html");
  } catch (error) {
    showToast(error.message || "Could not log out. Check your connection and try again.");
  }
}

profileMenuButton.addEventListener("click", () => {
  const isOpen = !profileDropdown.hidden;
  profileDropdown.hidden = isOpen;
  profileMenuButton.setAttribute("aria-expanded", String(!isOpen));
});

document.querySelector("[data-logout]").addEventListener("click", logout);

document.addEventListener("click", (event) => {
  if (!event.target.closest(".profile-menu")) {
    profileDropdown.hidden = true;
    profileMenuButton.setAttribute("aria-expanded", "false");
  }
});

document.addEventListener("keydown", (event) => {
  if (event.key === "Escape") {
    profileDropdown.hidden = true;
    profileMenuButton.setAttribute("aria-expanded", "false");
  }
});

function escapeHTML(value) {
  return String(value).replace(/[&<>"']/g, (character) => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;",
  })[character]);
}

function formatListingTime(createdAt) {
  if (!createdAt) return "Just now";
  const minutes = Math.max(0, Math.floor((Date.now() - new Date(createdAt).getTime()) / 60000));
  if (minutes < 1) return "Just now";
  if (minutes < 60) return `${minutes} min ago`;
  const hours = Math.floor(minutes / 60);
  if (hours < 24) return `${hours} hr${hours === 1 ? "" : "s"} ago`;
  return `${Math.floor(hours / 24)} day${hours < 48 ? "" : "s"} ago`;
}

function formatPrice(price) {
  return Number(price) === 0 ? "Free" : `₹${Number(price).toLocaleString("en-IN")}`;
}

function filteredListings() {
  const query = searchInput.value.trim().toLowerCase();
  const kind = currentView === "items" ? "item" : "gig";
  return listings.filter((listing) => {
    if (listing.kind !== kind) return false;
    if (currentCategory !== "all" && listing.category !== currentCategory) return false;
    if (query && !`${listing.title} ${listing.description} ${listing.category} ${listing.seller}`.toLowerCase().includes(query)) return false;
    return true;
  });
}

function renderListings() {
  const matches = filteredListings();
  const visible = showAll ? matches : matches.slice(0, 4);
  grid.innerHTML = visible.map((listing) => {
    const title = escapeHTML(listing.title);
    const description = escapeHTML(listing.description);
    const seller = escapeHTML(listing.seller);
    const tag = escapeHTML(listing.tag || (listing.kind === "gig" ? "STUDENT HELP" : "CAMPUS FIND"));
    const saved = savedIds.has(listing.id);
    const price = listing.kind === "gig" && listing.direction === "request"
      ? Number(listing.price) === 0 ? "Reward TBD" : `₹${Number(listing.price).toLocaleString("en-IN")} reward`
      : formatPrice(listing.price);
    const imageMarkup = listing.image
      ? `<img src="${escapeHTML(listing.image)}" alt="${title}" class="user-image"><span class="placeholder-art ${escapeHTML(listing.category)}" aria-hidden="true">${escapeHTML(listing.emoji || "✳")}</span>`
      : `<span class="placeholder-art ${escapeHTML(listing.category)}" aria-hidden="true">${escapeHTML(listing.emoji || "✳")}</span>`;
    return `<article class="listing-card">
      <div class="card-image">${imageMarkup}<span class="item-tag">${tag}</span>
        <button class="save-button${saved ? " saved" : ""}" type="button" data-save="${escapeHTML(listing.id)}" aria-label="${saved ? "Remove from" : "Add to"} saved listings" aria-pressed="${saved}">${saved ? "♥" : "♡"}</button>
      </div>
      <div class="card-content"><div class="card-title-row"><h3 class="card-title">${title}</h3><span class="card-price">${price}</span></div>
        <p class="card-description">${description}</p>
        <div class="card-meta"><span class="seller"><span class="seller-avatar">${escapeHTML(listing.initial || seller.charAt(0).toUpperCase())}</span>${seller}</span><span>${escapeHTML(formatListingTime(listing.createdAt))}</span></div>
        <button class="enquire-button" type="button" data-enquire="${escapeHTML(listing.id)}">Enquire <span aria-hidden="true">→</span></button>
      </div>
    </article>`;
  }).join("");
  grid.querySelectorAll(".user-image").forEach((image) => {
    image.addEventListener("error", () => image.classList.add("image-failed"), { once: true });
    image.addEventListener("load", () => {
      const placeholder = image.nextElementSibling;
      if (placeholder) placeholder.hidden = true;
    }, { once: true });
  });
  emptyState.hidden = matches.length > 0;
  grid.hidden = matches.length === 0;
  document.querySelector("#show-all").hidden = matches.length <= 4;
  document.querySelector("#show-all").innerHTML = showAll ? "Show fewer <span aria-hidden=\"true\">↑</span>" : "Show all listings <span aria-hidden=\"true\">→</span>";
  updateCounts();
}

function updateCounts() {
  document.querySelector('[data-view="items"] span').textContent = String(listings.filter((item) => item.kind === "item").length).padStart(2, "0");
  document.querySelector('[data-view="gigs"] span').textContent = String(listings.filter((item) => item.kind === "gig").length).padStart(2, "0");
}

function showToast(message) {
  toast.textContent = message;
  toast.classList.add("visible");
  window.clearTimeout(toastTimer);
  toastTimer = window.setTimeout(() => toast.classList.remove("visible"), 2800);
}

function openDialog(kind) {
  if (kind) kindSelect.value = kind;
  updateFormKind();
  dialog.showModal();
}

function updateFormKind() {
  const isGig = kindSelect.value === "gig";
  const isRequest = isGig && directionSelect.value === "request";
  const categorySelect = document.querySelector("#post-category");
  const helpCategory = categorySelect.querySelector('option[value="help"]');
  document.querySelector(".gig-direction-field").hidden = !isGig;
  document.querySelector("#price-label").textContent = isRequest ? "Reward offered (₹)" : isGig ? "Rate (₹)" : "Price (₹)";
  document.querySelector("#dialog-title").textContent = isRequest ? "Find help on campus" : isGig ? "Share a skill with campus" : "Share it with campus";
  document.querySelector("#post-title").placeholder = isGig ? "e.g. Tutoring for first-year calculus" : "e.g. Graphing calculator, barely used";
  document.querySelector("#form-hint").textContent = isGig
    ? "Keep it to tutoring, feedback, and project guidance — not completed coursework."
    : "Only post items you own and can hand over safely on campus.";
  helpCategory.hidden = !isGig;
  helpCategory.disabled = !isGig;
  if (isGig) categorySelect.value = "help";
  else if (categorySelect.value === "help") categorySelect.value = "books";
}

document.querySelectorAll(".market-tab").forEach((button) => {
  button.addEventListener("click", () => selectView(button.dataset.view));
});

function selectView(view) {
  currentView = view;
  currentCategory = "all";
  showAll = false;
  document.querySelectorAll(".market-tab").forEach((tab) => {
    const active = tab.dataset.view === view;
    tab.classList.toggle("active", active);
    tab.setAttribute("aria-selected", String(active));
  });
  document.querySelectorAll(".category-chip").forEach((chip) => {
    const category = chip.dataset.category;
    chip.hidden = view === "gigs" ? category !== "all" && category !== "help" : category === "help";
    chip.classList.toggle("active", category === "all");
  });
  renderListings();
}

document.querySelectorAll("[data-nav-view]").forEach((link) => {
  link.addEventListener("click", () => selectView(link.dataset.navView));
});

document.querySelectorAll(".category-chip").forEach((button) => {
  button.addEventListener("click", () => {
    currentCategory = button.dataset.category;
    showAll = false;
    document.querySelectorAll(".category-chip").forEach((chip) => chip.classList.toggle("active", chip === button));
    renderListings();
  });
});

searchInput.addEventListener("input", () => { showAll = false; renderListings(); });
document.querySelector("#show-all").addEventListener("click", () => { showAll = !showAll; renderListings(); });
document.querySelector("#clear-filters").addEventListener("click", () => {
  searchInput.value = "";
  currentCategory = "all";
  showAll = false;
  document.querySelectorAll(".category-chip").forEach((chip) => chip.classList.toggle("active", chip.dataset.category === "all"));
  renderListings();
});
document.querySelectorAll("[data-open-modal]").forEach((button) => button.addEventListener("click", () => openDialog(button.dataset.kind)));
document.querySelectorAll("[data-close-modal]").forEach((button) => button.addEventListener("click", () => dialog.close()));
kindSelect.addEventListener("change", updateFormKind);
directionSelect.addEventListener("change", updateFormKind);
dialog.addEventListener("click", (event) => {
  if (event.target === dialog) dialog.close();
});
grid.addEventListener("click", async (event) => {
  const enquireButton = event.target.closest("[data-enquire]");
  if (enquireButton) {
    const listing = listings.find((item) => item.id === enquireButton.dataset.enquire);
    if (!listing || !listing.email) {
      showToast("This poster's email is unavailable. Try again later.");
      return;
    }

    const message = `I am interested in ${listing.title}.`;
    const gmailUrl = new URL("https://mail.google.com/mail/u/0/");
    gmailUrl.searchParams.set("view", "cm");
    gmailUrl.searchParams.set("fs", "1");
    gmailUrl.searchParams.set("to", listing.email);
    gmailUrl.searchParams.set("su", message);
    gmailUrl.searchParams.set("body", message);
    window.open(gmailUrl.href, "_blank", "noopener");
    return;
  }
  const button = event.target.closest("[data-save]");
  if (!button) return;
  const id = button.dataset.save;
  const action = savedIds.has(id) ? "remove" : "save";
  button.disabled = true;
  try {
    const response = await fetch("api/favorites.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ action, listingId: id }),
    });
    const result = await response.json();
    if (!response.ok) throw new Error(result.error || "Could not update your saved listings.");
    if (action === "save") savedIds.add(id);
    else savedIds.delete(id);
    renderListings();
    showToast(action === "save" ? "Saved to your favorites." : "Removed from your favorites.");
  } catch (error) {
    showToast(error.message || "Could not update your saved listings. Try again.");
  } finally {
    if (button.isConnected) button.disabled = false;
  }
});

form.addEventListener("submit", async (event) => {
  event.preventDefault();
  const data = new FormData(form);
  const kind = data.get("kind");
  const imageFile = data.get("image");
  const submitButton = form.querySelector('button[type="submit"]');
  submitButton.disabled = true;
  try {
    let image = null;
    if (imageFile instanceof File && imageFile.size > 0) {
      if (!["image/png", "image/jpeg", "image/gif", "image/webp"].includes(imageFile.type)) {
        throw new Error("Choose a PNG, JPEG, GIF, or WebP image.");
      }
      if (imageFile.size > 1024 * 1024) {
        throw new Error("Choose an image under 1 MB.");
      }
      image = await new Promise((resolve, reject) => {
        const reader = new FileReader();
        reader.addEventListener("load", () => resolve(reader.result), { once: true });
        reader.addEventListener("error", () => reject(new Error("Couldn't load that photo. Try a different image.")), { once: true });
        reader.readAsDataURL(imageFile);
      });
    }

    const response = await fetch("api/listings.php", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        kind,
        direction: kind === "gig" ? data.get("direction") : null,
        title: data.get("title"),
        description: data.get("description"),
        price: data.get("price"),
        category: data.get("category"),
        image,
      }),
    });
    const result = await response.json();
    if (!response.ok) throw new Error(result.error || "Your post could not be saved.");

    const listingsResponse = await fetch("api/listings.php");
    const listingsResult = await listingsResponse.json();
    if (!listingsResponse.ok) throw new Error(listingsResult.error || "Your post was saved, but listings could not be refreshed.");
    listings = listingsResult.listings;

    form.reset();
    kindSelect.value = kind;
    updateFormKind();
    searchInput.value = "";
    selectView(kind === "item" ? "items" : "gigs");
    showAll = true;
    dialog.close();
    renderListings();
    document.querySelector("#marketplace").scrollIntoView({ behavior: "smooth" });
    showToast("Your post is live on campus.");
  } catch (error) {
    showToast(error.message || "Your post could not be saved. Try again.");
  } finally {
    submitButton.disabled = false;
  }
});

document.addEventListener("keydown", (event) => {
  if ((event.metaKey || event.ctrlKey) && event.key.toLowerCase() === "k") {
    event.preventDefault();
    searchInput.focus();
  }
});

async function initializeApp() {
  try {
    const sessionResponse = await fetch("api/auth.php?action=session");
    const session = await sessionResponse.json();
    if (!sessionResponse.ok || !session.authenticated) {
      window.location.replace("login.html");
      return;
    }

    const [listingsResponse, favoritesResponse] = await Promise.all([
      fetch("api/listings.php"),
      fetch("api/favorites.php"),
    ]);
    const [result, favorites] = await Promise.all([
      listingsResponse.json(),
      favoritesResponse.json(),
    ]);
    if (!listingsResponse.ok) {
      if (listingsResponse.status === 401) {
        window.location.replace("login.html");
        return;
      }
      throw new Error(result.error || "Could not load campus listings.");
    }
    if (!favoritesResponse.ok) {
      if (favoritesResponse.status === 401) {
        window.location.replace("login.html");
        return;
      }
      throw new Error(favorites.error || "Could not load your saved listings.");
    }

    listings = result.listings;
    savedIds = new Set(favorites.listingIds);
    if (session.user.displayName) {
      profileMenuButton.textContent = session.user.displayName.charAt(0).toUpperCase();
    }
    document.body.hidden = false;
    renderListings();
  } catch (error) {
    document.body.hidden = false;
    showToast(error.message || "Could not connect to Campify. Check that PHP and Supabase are running.");
  }
}

initializeApp();

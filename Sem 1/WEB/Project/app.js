const defaultListings = [
  { id: "book-1", kind: "item", title: "Calculus, 8th edition", description: "Clean pages, great for the first-year maths course.", price: 450, category: "books", seller: "Ananya", initial: "A", time: "12 min ago", emoji: "📚", tag: "GREAT CONDITION" },
  { id: "tech-1", kind: "item", title: "Wireless headphones", description: "Good sound, comfy fit. Selling since I upgraded.", price: 1200, category: "tech", seller: "Rohan", initial: "R", time: "38 min ago", emoji: "🎧", tag: "PRICE DROP" },
  { id: "living-1", kind: "item", title: "Study desk lamp", description: "Warm light, adjustable neck. Includes the bulb.", price: 350, category: "living", seller: "Meera", initial: "M", time: "1 hr ago", emoji: "💡", tag: "LIKE NEW" },
  { id: "style-1", kind: "item", title: "Canvas tote bag", description: "Roomy everyday tote, barely used.", price: 180, category: "style", seller: "Diya", initial: "D", time: "2 hrs ago", emoji: "👜", tag: "CAMPUS PICK" },
  { id: "book-2", kind: "item", title: "Data structures notes", description: "My neatly organized notes from last semester.", price: 150, category: "books", seller: "Kabir", initial: "K", time: "3 hrs ago", emoji: "📝", tag: "STUDENT FAV" },
  { id: "tech-2", kind: "item", title: "Scientific calculator", description: "All buttons work perfectly. Great for exams.", price: 600, category: "tech", seller: "Nisha", initial: "N", time: "4 hrs ago", emoji: "🧮", tag: "READY TO GO" },
  { id: "living-2", kind: "item", title: "Indoor desk plant", description: "Low-maintenance pothos cutting in a ceramic pot.", price: 120, category: "living", seller: "Sana", initial: "S", time: "5 hrs ago", emoji: "🪴", tag: "LITTLE GREEN" },
  { id: "style-2", kind: "item", title: "Denim jacket", description: "Classic blue, size M. Pick up near the library.", price: 700, category: "style", seller: "Arjun", initial: "A", time: "Yesterday", emoji: "🧥", tag: "GOOD FIND" },
  { id: "help-1", kind: "gig", title: "Intro to Python tutoring", description: "Friendly one-on-one sessions to work through the basics together.", price: 250, category: "help", seller: "Priya", initial: "P", time: "20 min ago", emoji: "🐍", tag: "TUTORING" },
  { id: "help-2", kind: "gig", direction: "request", title: "Looking for a project brainstorm buddy", description: "Help me plan milestones and work through a couple of tricky parts.", price: 0, category: "help", seller: "Dev", initial: "D", time: "1 hr ago", emoji: "💡", tag: "HELP WANTED" },
  { id: "help-3", kind: "gig", title: "Poster & presentation design", description: "I'll help you make your own ideas look polished and presentation-ready.", price: 400, category: "help", seller: "Tara", initial: "T", time: "2 hrs ago", emoji: "🎨", tag: "DESIGN" },
  { id: "help-4", kind: "gig", direction: "request", title: "Need a calculus study partner", description: "Looking for someone to review limits and derivatives together.", price: 200, category: "help", seller: "Vikram", initial: "V", time: "3 hrs ago", emoji: "📐", tag: "HELP WANTED" },
  { id: "help-5", kind: "gig", title: "Portfolio feedback", description: "Constructive feedback on your design or dev portfolio, from a fellow student.", price: 0, category: "help", seller: "Nina", initial: "N", time: "5 hrs ago", emoji: "🖥️", tag: "FEEDBACK" },
  { id: "help-6", kind: "gig", title: "Excel basics, made easy", description: "Learn the formulas and shortcuts I wish I knew in first year.", price: 180, category: "help", seller: "Ishaan", initial: "I", time: "Yesterday", emoji: "📊", tag: "SKILL SHARE" },
];

const storageKeys = { listings: "campify-listings-v1", saved: "campify-saved-v1" };
let listings = readStorage(storageKeys.listings, []);
let savedIds = new Set(readStorage(storageKeys.saved, []));
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
const authStorageKey = "campify-auth-session-v1";
let currentUserEmail = "";
const profileMenuButton = document.querySelector("[data-profile-menu]");
const profileDropdown = document.querySelector(".profile-dropdown");

try {
  const session = JSON.parse(sessionStorage.getItem(authStorageKey) || "null");
  currentUserEmail = session?.email || "";
  const avatarButton = document.querySelector("[data-profile-menu]");
  if (session?.displayName && avatarButton) {
    avatarButton.textContent = session.displayName.charAt(0).toUpperCase();
  }
} catch (error) {
  console.warn("Campify could not read the display name from the login session.", error);
}

function logout() {
    try {
      sessionStorage.removeItem(authStorageKey);
    } catch (error) {
      console.warn("Campify could not clear the login session.", error);
    }
    window.location.replace("login.html");
}

profileMenuButton.addEventListener("click", () => {
  const isOpen = !profileDropdown.hidden;
  profileDropdown.hidden = isOpen;
  profileMenuButton.setAttribute("aria-expanded", String(!isOpen));
});

document.querySelector("[data-profile]").addEventListener("click", () => {
  profileDropdown.hidden = true;
  profileMenuButton.setAttribute("aria-expanded", "false");
  showToast("Profile settings are coming soon.");
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

function readStorage(key, fallback) {
  try {
    const stored = localStorage.getItem(key);
    return stored ? JSON.parse(stored) : fallback;
  } catch (error) {
    console.warn(`Campify could not read saved data (${key}).`, error);
    return fallback;
  }
}

function writeStorage(key, value) {
  try {
    localStorage.setItem(key, JSON.stringify(value));
    return true;
  } catch (error) {
    console.warn(`Campify could not save data (${key}).`, error);
    showToast("Your browser couldn't save this change. Check available storage.");
    return false;
  }
}

function escapeHTML(value) {
  return String(value).replace(/[&<>"']/g, (character) => ({
    "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;",
  })[character]);
}

function formatPrice(price) {
  return Number(price) === 0 ? "Free" : `₹${Number(price).toLocaleString("en-IN")}`;
}

function getListingEmail(listing) {
  if (listing.email) return listing.email;
  return `${String(listing.seller).toLowerCase().replace(/[^a-z0-9]+/g, ".")}@mgits.ac.in`;
}

function filteredListings() {
  const query = searchInput.value.trim().toLowerCase();
  const kind = currentView === "items" ? "item" : "gig";
  return [...listings, ...defaultListings].filter((listing) => {
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
    const listingEmail = escapeHTML(getListingEmail(listing));
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
        <div class="card-meta"><span class="seller"><span class="seller-avatar">${escapeHTML(listing.initial || seller.charAt(0).toUpperCase())}</span>${seller}</span><span>${escapeHTML(listing.time || "Just now")}</span></div>
        <button class="enquire-button" type="button" data-enquire="${escapeHTML(listing.id)}" data-email="${listingEmail}" data-title="${title}">Enquire <span aria-hidden="true">→</span></button>
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
  document.querySelector('[data-view="items"] span').textContent = String([...listings, ...defaultListings].filter((item) => item.kind === "item").length).padStart(2, "0");
  document.querySelector('[data-view="gigs"] span').textContent = String([...listings, ...defaultListings].filter((item) => item.kind === "gig").length).padStart(2, "0");
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
  document.querySelector(".gig-direction-field").hidden = !isGig;
  document.querySelector("#price-label").textContent = isRequest ? "Reward offered (₹)" : isGig ? "Rate (₹)" : "Price (₹)";
  document.querySelector("#dialog-title").textContent = isRequest ? "Find help on campus" : isGig ? "Share a skill with campus" : "Share it with campus";
  document.querySelector("#post-title").placeholder = isGig ? "e.g. Tutoring for first-year calculus" : "e.g. Graphing calculator, barely used";
  document.querySelector("#form-hint").textContent = isGig
    ? "Keep it to tutoring, feedback, and project guidance — not completed coursework."
    : "Only post items you own and can hand over safely on campus.";
  if (isGig) document.querySelector("#post-category").value = "help";
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
grid.addEventListener("click", (event) => {
  const enquireButton = event.target.closest("[data-enquire]");
  if (enquireButton) {
    const title = enquireButton.dataset.title;
    const recipient = enquireButton.dataset.email;
    const subject = `I'm interested in ${title}`;
    const body = `I'm interested in ${title}`;
    const gmailUrl = `https://mail.google.com/mail/?view=cm&fs=1&to=${encodeURIComponent(recipient)}&su=${encodeURIComponent(subject)}&body=${encodeURIComponent(body)}`;
    window.open(gmailUrl, "_blank", "noopener,noreferrer");
    return;
  }
  const button = event.target.closest("[data-save]");
  if (!button) return;
  const id = button.dataset.save;
  if (savedIds.has(id)) savedIds.delete(id);
  else savedIds.add(id);
  writeStorage(storageKeys.saved, [...savedIds]);
  renderListings();
  showToast(savedIds.has(id) ? "Saved to your favorites." : "Removed from your favorites.");
});

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const data = new FormData(form);
  const kind = data.get("kind");
  const imageFile = data.get("image");
  const saveListing = (image) => {
    const seller = "You";
    const listing = {
      id: `user-${Date.now()}`,
      kind,
      title: data.get("title").trim(),
      description: data.get("description").trim(),
      price: Number(data.get("price")),
      category: kind === "gig" ? "help" : data.get("category"),
      ...(kind === "gig" ? { direction: data.get("direction") } : {}),
      seller,
      email: currentUserEmail,
      initial: "Y",
      time: "Just now",
      emoji: kind === "gig" ? "✳" : "📦",
      tag: kind === "gig" ? (data.get("direction") === "request" ? "HELP WANTED" : "STUDENT HELP") : "JUST LISTED",
      ...(image ? { image } : {}),
    };
    listings.unshift(listing);
    const stored = writeStorage(storageKeys.listings, listings);
    form.reset();
    kindSelect.value = kind;
    updateFormKind();
    searchInput.value = "";
    selectView(kind === "item" ? "items" : "gigs");
    showAll = true;
    dialog.close();
    renderListings();
    document.querySelector("#marketplace").scrollIntoView({ behavior: "smooth" });
    showToast(stored ? "Your post is live on this device." : "Your post is available for this session, but couldn't be saved.");
  };
  if (imageFile instanceof File && imageFile.size > 0) {
    if (!imageFile.type.startsWith("image/")) {
      showToast("Please choose an image file.");
      return;
    }
    if (imageFile.size > 2 * 1024 * 1024) {
      showToast("Please choose an image under 2 MB.");
      return;
    }
    const reader = new FileReader();
    reader.addEventListener("load", () => saveListing(reader.result), { once: true });
    reader.addEventListener("error", () => showToast("Couldn't load that photo. Try a different image."), { once: true });
    reader.readAsDataURL(imageFile);
  } else {
    saveListing(null);
  }
});

document.addEventListener("keydown", (event) => {
  if ((event.metaKey || event.ctrlKey) && event.key.toLowerCase() === "k") {
    event.preventDefault();
    searchInput.focus();
  }
});

renderListings();

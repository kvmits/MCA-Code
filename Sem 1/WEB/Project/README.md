# Campify

Campify is a static campus marketplace front-end. Open `login.html` to create an account or sign in.

Authentication is intentionally browser-only for this front-end project: registration requires an email ending in `@mgits.ac.in`, account records are stored in `localStorage`, passwords are salted and derived with PBKDF2 through Web Crypto, and the active login session is stored in `sessionStorage`. A production deployment should replace this with a server-backed authentication service, HTTPS, secure cookies, email verification, and verified campus membership.
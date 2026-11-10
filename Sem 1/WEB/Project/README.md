# Campify

Campify is a campus marketplace with Supabase-backed authentication and listings. Passwords are handled by Supabase Auth; the PHP API keeps access and refresh tokens in an HTTP-only server session. College-email restrictions are checked by the PHP API and a database trigger. Listings are stored in Supabase with row-level security so only signed-in students can read them and each student can only create or change their own posts.

## One-time Supabase setup

1. Open the Supabase project configured in `db.php`.
2. In **SQL Editor**, run the complete [`schema.sql`](./schema.sql). If you already ran an earlier version, run the updated file again to add the `delisted_at` column and secure account-deletion function. It creates the protected `listings` and `listing_favorites` tables, row-level-security policies, and sample marketplace posts.
3. In **Authentication → Providers**, enable email/password sign-in.
4. In **Authentication → URL Configuration**, set the local Site URL to `http://localhost:8000` and add `http://localhost:8000/auth-confirmation.html` to the allowed Redirect URLs.
5. If email confirmation is enabled, new students must confirm their college email before signing in.
6. Supabase's built-in email sender is for testing and may only send to addresses on the Supabase organization team. To send confirmation emails to students, configure a custom SMTP provider under **Project Settings → Authentication → SMTP Settings** (the menu may also appear under Authentication settings).

The supplied publishable key cannot create tables, so the SQL Editor step must be completed by someone with Supabase project access.
Do not put database passwords or Supabase service-role keys in source files; rotate credentials if they have been shared in plain text.

## Run locally

Use PHP 8.0+ with the cURL and mbstring extensions enabled. From this folder, run:

```powershell
php -S localhost:8000
```

Then open `http://localhost:8000/login.html`. Do not open the HTML files directly with `file://`; the PHP API and session cookie need a web server.

Registration is restricted to `@mgits.ac.in` addresses. Accounts, sessions, marketplace listings, and saved favorites are server-backed. The profile page shows the signed-in student's listings and supports delisting posts (retained in the profile with a timestamp), password changes, and password-confirmed account deletion. Account deletion uses a database function that can only delete the currently authenticated user, and removes that user's listings and saved favorites; no service-role key is needed. After signup, students see a check-your-email page; clicking Supabase's confirmation link verifies the address and starts their Campify session. Set `CAMPIFY_SITE_URL` to your public site origin when deploying (for example, `https://campify.example.com`). Uploaded listing images are stored in the listing record and limited to 1 MB.

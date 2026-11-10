begin;

create or replace function public.enforce_campus_email()
returns trigger
language plpgsql
security definer
set search_path = ''
as $function$
begin
    if new.email is null or lower(new.email) !~ '^[^@]+@mgits[.]ac[.]in$' then
        raise exception 'A valid campus email address is required.' using errcode = '23514';
    end if;
    return new;
end;
$function$;

drop trigger if exists enforce_campus_email on auth.users;
create trigger enforce_campus_email
    before insert or update of email on auth.users
    for each row execute function public.enforce_campus_email();

revoke all on function public.enforce_campus_email() from public, anon, authenticated;

create table if not exists public.listings (
    id uuid primary key default gen_random_uuid(),
    owner_id uuid references auth.users (id) on delete set null,
    kind text not null check (kind in ('item', 'gig')),
    direction text check (direction in ('offer', 'request')),
    title text not null check (char_length(title) between 3 and 60),
    description text not null check (char_length(description) between 3 and 240),
    price numeric(10, 2) not null check (price between 0 and 9999999),
    category text not null check (category in ('books', 'tech', 'living', 'style', 'help', 'other')),
    seller_name text not null check (char_length(seller_name) between 2 and 40),
    emoji text not null default '✳',
    tag text not null default 'CAMPUS FIND',
    image_url text check (image_url is null or char_length(image_url) <= 1400000),
    created_at timestamptz not null default now(),
    delisted_at timestamptz,
    constraint listing_direction_matches_kind check (
        (kind = 'item' and direction is null and category <> 'help')
        or (kind = 'gig' and direction is not null and category = 'help')
    )
);

alter table public.listings add column if not exists delisted_at timestamptz;
create index if not exists listings_active_created_at_idx
    on public.listings (created_at desc)
    where delisted_at is null;

alter table public.listings enable row level security;

drop policy if exists "Authenticated users can read listings" on public.listings;
create policy "Authenticated users can read listings"
    on public.listings for select
    to authenticated
    using (auth.uid() is not null);

drop policy if exists "Users can create their own listings" on public.listings;
create policy "Users can create their own listings"
    on public.listings for insert
    to authenticated
    with check (owner_id = auth.uid());

drop policy if exists "Users can update their own listings" on public.listings;
create policy "Users can update their own listings"
    on public.listings for update
    to authenticated
    using (owner_id = auth.uid())
    with check (owner_id = auth.uid());

drop policy if exists "Users can delete their own listings" on public.listings;
create policy "Users can delete their own listings"
    on public.listings for delete
    to authenticated
    using (owner_id = auth.uid());

grant select, insert, update, delete on public.listings to authenticated;

create table if not exists public.listing_favorites (
    owner_id uuid not null references auth.users (id) on delete cascade,
    listing_id uuid not null references public.listings (id) on delete cascade,
    created_at timestamptz not null default now(),
    primary key (owner_id, listing_id)
);

alter table public.listing_favorites enable row level security;

drop policy if exists "Users can read their own favorites" on public.listing_favorites;
create policy "Users can read their own favorites"
    on public.listing_favorites for select
    to authenticated
    using (owner_id = auth.uid());

drop policy if exists "Users can save their own favorites" on public.listing_favorites;
create policy "Users can save their own favorites"
    on public.listing_favorites for insert
    to authenticated
    with check (owner_id = auth.uid());

drop policy if exists "Users can remove their own favorites" on public.listing_favorites;
create policy "Users can remove their own favorites"
    on public.listing_favorites for delete
    to authenticated
    using (owner_id = auth.uid());

grant select, insert, delete on public.listing_favorites to authenticated;

create or replace function public.delete_own_account()
returns void
language plpgsql
security definer
set search_path = ''
as $function$
declare
    current_user_id uuid := auth.uid();
begin
    if current_user_id is null then
        raise exception 'Sign in is required to delete an account.' using errcode = '42501';
    end if;

    delete from public.listings where owner_id = current_user_id;
    delete from auth.users where id = current_user_id;
    if not found then
        raise exception 'The account could not be found.' using errcode = 'P0002';
    end if;
end;
$function$;

revoke all on function public.delete_own_account() from public, anon;
grant execute on function public.delete_own_account() to authenticated;

insert into public.listings
    (id, kind, direction, title, description, price, category, seller_name, emoji, tag, created_at)
values
    ('00000000-0000-4000-8000-000000000001', 'item', null, 'Calculus, 8th edition', 'Clean pages, great for the first-year maths course.', 450, 'books', 'Ananya', '📚', 'GREAT CONDITION', now() - interval '12 minutes'),
    ('00000000-0000-4000-8000-000000000002', 'item', null, 'Wireless headphones', 'Good sound, comfy fit. Selling since I upgraded.', 1200, 'tech', 'Rohan', '🎧', 'PRICE DROP', now() - interval '38 minutes'),
    ('00000000-0000-4000-8000-000000000003', 'item', null, 'Study desk lamp', 'Warm light, adjustable neck. Includes the bulb.', 350, 'living', 'Meera', '💡', 'LIKE NEW', now() - interval '1 hour'),
    ('00000000-0000-4000-8000-000000000004', 'item', null, 'Canvas tote bag', 'Roomy everyday tote, barely used.', 180, 'style', 'Diya', '👜', 'CAMPUS PICK', now() - interval '2 hours'),
    ('00000000-0000-4000-8000-000000000005', 'item', null, 'Data structures notes', 'My neatly organized notes from last semester.', 150, 'books', 'Kabir', '📝', 'STUDENT FAV', now() - interval '3 hours'),
    ('00000000-0000-4000-8000-000000000006', 'item', null, 'Scientific calculator', 'All buttons work perfectly. Great for exams.', 600, 'tech', 'Nisha', '🧮', 'READY TO GO', now() - interval '4 hours'),
    ('00000000-0000-4000-8000-000000000007', 'item', null, 'Indoor desk plant', 'Low-maintenance pothos cutting in a ceramic pot.', 120, 'living', 'Sana', '🪴', 'LITTLE GREEN', now() - interval '5 hours'),
    ('00000000-0000-4000-8000-000000000008', 'item', null, 'Denim jacket', 'Classic blue, size M. Pick up near the library.', 700, 'style', 'Arjun', '🧥', 'GOOD FIND', now() - interval '1 day'),
    ('00000000-0000-4000-8000-000000000009', 'gig', 'offer', 'Intro to Python tutoring', 'Friendly one-on-one sessions to work through the basics together.', 250, 'help', 'Priya', '🐍', 'TUTORING', now() - interval '20 minutes'),
    ('00000000-0000-4000-8000-000000000010', 'gig', 'request', 'Looking for a project brainstorm buddy', 'Help me plan milestones and work through a couple of tricky parts.', 0, 'help', 'Dev', '💡', 'HELP WANTED', now() - interval '1 hour'),
    ('00000000-0000-4000-8000-000000000011', 'gig', 'offer', 'Poster & presentation design', 'I will help you make your own ideas look polished and presentation-ready.', 400, 'help', 'Tara', '🎨', 'DESIGN', now() - interval '2 hours'),
    ('00000000-0000-4000-8000-000000000012', 'gig', 'request', 'Need a calculus study partner', 'Looking for someone to review limits and derivatives together.', 200, 'help', 'Vikram', '📐', 'HELP WANTED', now() - interval '3 hours'),
    ('00000000-0000-4000-8000-000000000013', 'gig', 'offer', 'Portfolio feedback', 'Constructive feedback on your design or dev portfolio, from a fellow student.', 0, 'help', 'Nina', '🖥️', 'FEEDBACK', now() - interval '5 hours'),
    ('00000000-0000-4000-8000-000000000014', 'gig', 'offer', 'Excel basics, made easy', 'Learn the formulas and shortcuts I wish I knew in first year.', 180, 'help', 'Ishaan', '📊', 'SKILL SHARE', now() - interval '1 day')
on conflict (id) do nothing;

commit;

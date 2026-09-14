# LibrarySystem

A small C++ library management system, built primarily as a learning exercise to practice core C++ fundamentals: raw pointers, references, manual memory management, polymorphism, and ownership design. The "library" domain is the vehicle — the real goal was to get hands-on with the mechanics that `std::vector`, `std::unique_ptr`, and friends normally hide.

## Why this project

I wanted something more concrete than isolated pointer exercises, but small enough to finish in a couple of focused sessions. A library system gave a natural set of ownership questions to answer explicitly rather than default around:

- Does a collection own the objects it holds, or just reference them?
- When should something be a pointer, a reference, or a plain value?
- What happens to memory when a container resizes, copies, or goes out of scope?

Every design decision below was made deliberately, not by default — that's the actual point of the project.

## Features

- Add, remove, and list catalog items (`Book`, extensible via polymorphism to other `Item` types)
- Register library members with a borrowing limit
- Borrow and return items, with validation (availability, member limits, existence checks)
- Borrow records with automatic due-date calculation (borrow date + fixed loan period)
- Full catalog printing showing availability status per item

## Architecture

| Class | Responsibility |
|---|---|
| `Item` | Abstract base class for anything the library can lend (title, author, ID, availability, virtual `display()`) |
| `Book` | Concrete `Item` (ISBN, genre, page count) |
| `Member` | A registered library user; tracks currently borrowed items and enforces a borrowing limit |
| `BorrowRecord` | A single borrow transaction linking an item and a member, with borrow/due dates |
| `Date` | Minimal date value type with day-arithmetic (used for due-date calculation) |
| `ItemCollection` | Hand-rolled, array-backed container for `Item*` — the core memory-management exercise of the project |
| `Library` | Orchestrates the above; the only class `main` needs to talk to |

### Key design decisions

**`ItemCollection` is a raw dynamic array, not `std::vector`.** This is deliberate — it's the piece of the project meant to force manual resize logic, rule-of-three/five reasoning, and explicit ownership decisions instead of relying on standard containers to hide them.

**`ItemCollection` owns its items.** It deletes every `Item*` it holds in its destructor. Because deep-copying a polymorphic collection safely requires a `clone()` pattern that was out of scope here, copy construction and copy assignment are explicitly deleted (`= delete`) rather than left to an unsafe compiler-generated default.

**`Member` is stored as `std::vector<Member*>`, not `std::vector<Member>`.** `Member` objects need a stable memory address — other parts of the system (indirectly, via ID lookup) depend on referring to "this exact member" over time. A value-vector would risk moving/copying `Member` objects during a resize; a pointer-vector guarantees identity stability.

**`BorrowRecord` is stored as `std::vector<BorrowRecord>` (by value), not by pointer.** Unlike `Member`, nothing holds a long-lived reference to a specific `BorrowRecord` — records are looked up fresh by scanning the vector each time they're needed. Since nothing depends on a record's address staying fixed, storing by value is simpler and avoids an unnecessary heap allocation per transaction.

**Lookups use IDs, not pointers, at the `Library` interface.** It's tempting to think passing a pointer directly is "safer" than passing an ID that might not exist. In practice it's the opposite: an ID that doesn't match anything fails a lookup cleanly and predictably, while a stale or already-freed pointer passed in from outside produces undefined behavior with no safety net. Pointers are used internally, between objects that are created and destroyed together (e.g. a `BorrowRecord` referencing an `Item*`) — not at the boundary where external code drives the system.

**Failure handling is return-value based (`bool`), not exception-based, for expected/routine failures.** "Item not found," "member at borrowing limit," "item already borrowed" are normal, anticipated outcomes a caller should handle as regular control flow, not exceptional circumstances — this follows fairly standard C++ practice of reserving exceptions for truly unrecoverable or invariant-violating situations. The one deliberate exception to this: `Member::registerMember` throws on an empty name, treated as invalid construction input rather than a routine runtime condition.

## Building

Standard CMake + C++17 project. From the project root:

```
cmake -B build
cmake --build build
```

Run the produced executable from the `build` directory.

## What's not here (yet)

This was scoped as a short learning exercise, not a finished tool, so a few things a "real" version would need are intentionally out of scope for now:

- **Persistence** — everything lives in memory; state resets on every run.
- **Automated tests** — correctness was verified manually via `main.cpp` test sequences during development, not via a test framework.
- **Search by title/author, list-borrowed-by-member** — specified in the original design but not yet implemented.

## License

MIT

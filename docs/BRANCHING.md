# Branching strategy and commits

## Branches

| Branch | Purpose |
|---|---|
| `main` | Always builds and passes all tests. Only changed by pull request. Release tags are made here |
| `feature/<name>` | One feature or task, branched from `main`. Example: `feature/sqlite-user-repository` |
| `fix/<name>` | A bug fix, found in testing. Example: `fix/late-penalty-boundary` |
| `release/v1.1` | Optional. Used for the maintenance change CR1 |

## Workflow

1. Create a branch from `main`: `git switch -c feature/<name>`.
2. Commit small, working steps.
3. Push the branch and open a pull request into `main`.
4. CI builds the project and runs the tests on every push. Merge only when CI is green.
5. Review your own pull request against the checklist in `docs/` (self code review, Phase 6) and note what you changed.
6. Delete the branch after merging.

## Commit messages

Format: `type(scope): short summary in the present tense`

| Type | Use for |
|---|---|
| `feat` | A new feature |
| `fix` | A bug fix |
| `test` | Adding or changing tests |
| `docs` | Documentation only |
| `refactor` | Code change that does not change behaviour |
| `build` | CMake, CI and tooling |
| `chore` | Other housekeeping |

Examples: `feat(domain): add tiered penalty policy`, `test(domain): cover 72-hour boundary`.

## Releases

Tags use semantic versions and are made on `main`: `v1.0.0` for the first release and `v1.1.0` for the maintenance release. Create with `git tag -a v1.0.0 -m "Release 1.0.0"` and `git push origin v1.0.0`.

# Repository Access and Branch Protection

This file describes the intended controls for `Master-Chiken/SW_RACER_RE`. It is a setup checklist, not proof that the GitHub settings have already been enabled.

## The operating model

- **Project Owner:** retains repository administration and final authority over what enters `master`.
- **Trusted core contributors:** can receive collaborator write access so they can commit, push feature branches, develop full features, and iterate in pull requests. On a personal-account repository, collaborator write access is broad, so invite only people you trust.
- **Everyone else:** can fork this public repository, build/test their own copy, and propose changes through a pull request. A fork does not give them write access to this repository. Nothing from an external pull request enters `master` until it is merged.
- **No direct edits to `master`:** require a pull request and owner review before merging.

This approach gives active contributors room to develop, while making the official branch the controlled integration point.

## GitHub configuration checklist

Open [Settings → Branches](https://github.com/Master-Chiken/SW_RACER_RE/settings/branches) in the repository. Create a branch protection rule for `master` (or create an active branch ruleset targeting the default branch) and configure:

- [ ] Require a pull request before merging.
- [ ] Require at least 1 approving review.
- [ ] Require review from Code Owners.
- [ ] Dismiss stale pull request approvals when new commits are pushed.
- [ ] Require conversation resolution before merging.
- [ ] Block force pushes.
- [ ] Block branch deletion.
- [ ] Do not add contributors or apps to a bypass list for the default branch.
- [ ] Do not enable any option that lets specified contributors bypass required pull requests.
- [ ] Keep administrator control with the Project Owner. Decide deliberately whether the owner must follow the same approval rule; if you require approvals from the owner on every change and prohibit all admin bypasses, another eligible reviewer will be needed for the owner's own pull requests.

The existing `.github/CODEOWNERS` file names `@Master-Chiken` as owner of every path. The approval rule must be enabled in GitHub settings for that designation to become a merge requirement.

## How to admit a trusted contributor

1. Discuss the intended role, the part of the code they will own, how reviews work, and whether they need direct write access.
2. Start them with a fork/PR if practical. Confirm they communicate clearly, test their changes, and respond constructively to review.
3. If branch-level collaboration is needed, invite them via **Settings → Collaborators**. Never add them as an administrator for convenience.
4. Give them a clearly scoped technical responsibility in `GOVERNANCE.md` or an issue, and review their first changes closely.
5. Revisit access when their role changes. Remove access when it is no longer needed.

## Important limitations

GitHub cannot stop people from cloning or forking a public repository. It can stop those people from writing to this repository directly. Public users may still propose a pull request; that proposal is not an accepted change. Never put passwords, tokens, secrets, original commercial game executables, or third-party proprietary assets in the repository.

On repositories owned by a personal GitHub account, direct collaborators have broad read/write access rather than separate Read/Triage/Write/Maintain roles. If the project later needs distinct permissions for testers, triagers, developers, and maintainers, consider an organisation-owned repository before granting broader access.

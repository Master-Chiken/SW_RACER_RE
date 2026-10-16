# Project Governance and Roles

This document defines how decisions are made in this repository and how contributors can work together without giving away control of the project.

## Scope and ownership

This repository is the `Master-Chiken/SW_RACER_RE` working fork. These rules apply to this repository only; they do not grant control over the upstream project or its maintainers.

The repository owner is the **Project Owner and Lead**. The owner retains final authority over the roadmap, priorities, repository settings, collaborator access, releases, and which changes are merged.

The intention is to welcome meaningful contributions while keeping the project coherent, reviewable, and secure.

## Project roles

These are project responsibilities. They are not all separate GitHub permission levels.

### 1. Project Owner / Lead

**Decision authority: final.**

- Defines the project direction and priorities.
- Approves or rejects pull requests before changes enter `master`.
- Controls releases, repository settings, and access to the repository.
- Resolves disagreements about scope, architecture, and release readiness.
- Can delegate a task without delegating ownership or final decision authority.

Initially, only the repository owner should have administrative access.

### 2. Technical Area Lead

**Decision authority: advisory within an assigned area.**

Areas may include reverse engineering and Ghidra, C/C++ hooks, Python tooling, build/CI, testing, and documentation.

An area lead may propose tasks, help contributors, review technical evidence, and recommend whether a change is ready. The Project Owner keeps final merge and roadmap authority unless this responsibility is explicitly delegated.

Appoint area leads based on demonstrated contributions and constructive reviews, not simply because someone requests elevated access.

### 3. Core Contributor / Developer

**Freedom to implement; no unilateral control over the official branch.**

Core contributors may take ownership of substantial work: implement complete features, refactor modules, change algorithms, improve scripts, add tests, investigate multiple related functions, and maintain a technical area. They should coordinate early on changes that affect architecture or overlap with ongoing work, but they are not limited to trivial fixes.

- Works in a personal fork or a feature branch.
- May commit and push to their own branch; trusted invited collaborators may push feature branches in this repository.
- Can run builds/tests, open draft or ready pull requests, review proposed changes, and iterate based on feedback.
- Records evidence and validation for reverse-engineering changes.
- Cannot bypass the required review for `master` or merge their own changes unless the Project Owner has explicitly granted that authority.

New people can begin with forks and pull requests. Direct repository write access is reserved for contributors whom the Project Owner trusts with broad write permission.

### 4. Reverse-Engineering Researcher

Investigates one function, global variable, address, calling convention, or runtime behaviour at a time. Records the game version, evidence, confidence level, and remaining unknowns. A well-supported analysis is useful even when it does not yet include code.

### 5. Tester / Bug Reporter

Reproduces issues, records exact steps and environment details, checks proposed fixes, and reports results. Do not upload proprietary game files or unredacted personal paths.

### 6. Documentation / Tooling Contributor

Improves build instructions, scripts, checks, tests, onboarding, and developer experience. Contributions should be small, independently verifiable, and documented.

One person may hold several project roles. Roles can be earned, changed, or withdrawn by the Project Owner.

## Change approval policy

The intended policy for `master` is:

1. Every change goes through a pull request; direct pushes to `master` are blocked.
2. Pull requests describe the change, why it is needed, the evidence, tests, and known limitations.
3. The Project Owner reviews and explicitly approves changes before merge.
4. New commits invalidate stale approvals; relevant checks must pass and review conversations must be resolved.
5. Contributors are encouraged to propose complete, ambitious changes. Split a change only when it improves review, testing, or coordination—not just to restrict contributor scope.
6. Generated files should be regenerated from their source/template where appropriate, rather than edited manually.
7. No contributor should claim tests were run unless they actually were run.

The repository's `.github/CODEOWNERS` marks the Project Owner as the reviewer for every path. **CODEOWNERS is not enforcement by itself.** The Project Owner must enable branch protection or a branch ruleset in GitHub settings. Until that is done, treat this policy as documented intent rather than a guarantee enforced by GitHub. See [ACCESS_CONTROL.md](ACCESS_CONTROL.md).

## Access and trust

This repository is owned by a personal GitHub account. GitHub's personal-repository model distinguishes the owner from collaborators; direct collaborators receive broad read/write access rather than the fine-grained Read, Triage, Write, Maintain, and Admin roles available to organisation repositories.

Therefore:

- **Public visitors:** can read the public repository and work in their own forks. Their pull requests are proposals; they do not change this repository unless accepted.
- **New contributors:** begin with forks and pull requests. They can still implement full features independently.
- **Trusted core contributors:** once branch protection is configured, invite them as collaborators if they need to push feature branches directly to this repository. Explain that this is broad write access and requires trust.
- **Project Owner:** keeps repository administration and final merge/release decisions. Do not grant admin access just to make development easier.
- **If granular permissions become necessary:** consider an organisation-owned repository, where GitHub supports more detailed repository roles. Assess the ownership and migration implications before transferring anything.

The Project Owner can remove direct collaborator access at any time. Removing access does not remove copies someone has already cloned or downloaded, so do not put secrets or proprietary third-party files in the repository.

## How decisions are made

- Contributors can suggest priorities and challenge a technical conclusion with evidence.
- Technical disagreements should be resolved using reproducible evidence, tests, and the project scope.
- The Project Owner makes the final decision for this fork and records significant architectural or roadmap decisions in an issue or pull request when possible.
- Credit contributors in the relevant change history and release notes where appropriate.

## Getting started

Read [CONTRIBUTING.md](CONTRIBUTING.md), check the issue templates under `.github/ISSUE_TEMPLATE/`, and discuss work that may overlap with existing upstream efforts before starting a large task.

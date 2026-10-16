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

### 3. Contributor / Developer

**Decision authority: owns their proposed change, not the repository.**

- Works on a focused task in a personal fork or feature branch.
- Opens a pull request describing the change, evidence, and tests.
- Responds to review feedback and updates their pull request.
- Does not merge their own changes into `master` unless the Project Owner has explicitly authorised it.

A contributor does not need direct push access to participate. Forks and pull requests are the default entry path for new contributors.

### 4. Reverse-Engineering Researcher

Investigates one function, global variable, address, calling convention, or runtime behaviour at a time. Records the game version, evidence, confidence level, and remaining unknowns. A well-supported analysis is useful even when it does not yet include code.

### 5. Tester / Bug Reporter

Reproduces issues, records exact steps and environment details, checks proposed fixes, and reports results. Do not upload proprietary game files or unredacted personal paths.

### 6. Documentation / Tooling Contributor

Improves build instructions, scripts, checks, tests, onboarding, and developer experience. Contributions should be small, independently verifiable, and documented.

One person may hold several project roles. Roles can be earned, changed, or withdrawn by the Project Owner.

## Change approval policy

The default policy for `master` is:

1. Changes arrive through a pull request, not a direct push.
2. Pull requests explain the purpose, scope, evidence, validation, and any known limitations.
3. The Project Owner reviews and explicitly approves changes before merge.
4. Relevant checks must pass, and review conversations must be resolved.
5. Large or risky changes should be split into smaller pull requests.
6. Generated files should be regenerated from their source/template where appropriate, rather than edited manually.
7. No contributor should claim tests were run unless they were actually run.

The repository's `.github/CODEOWNERS` marks the Project Owner as the reviewer for every path. GitHub branch protection must also be enabled for this requirement to be enforced automatically; see the README's contribution section and the GitHub settings instructions maintained by the Project Owner.

## Access and trust

This repository is owned by a personal GitHub account. GitHub's personal-repository model distinguishes the owner from collaborators; direct collaborators receive broad read/write access rather than the fine-grained Read, Triage, Write, Maintain, and Admin roles available to organisation repositories.

Therefore:

- **New contributors:** use forks and pull requests; no direct collaborator invitation is required.
- **Trusted contributors who need direct push access:** invite only after discussing the scope and expectations. Protect `master` first.
- **Never grant administrative access merely to make contribution easier.** Keep it with the Project Owner.
- **If granular permissions become necessary:** consider an organisation-owned repository, where GitHub supports more detailed repository roles. Assess the ownership and migration implications before transferring anything.

The Project Owner can remove direct collaborator access at any time. Removing access does not remove copies someone has already cloned or downloaded, so do not put secrets or proprietary third-party files in the repository.

## How decisions are made

- Contributors can suggest priorities and challenge a technical conclusion with evidence.
- Technical disagreements should be resolved using reproducible evidence, tests, and the project scope.
- The Project Owner makes the final decision for this fork and records significant architectural or roadmap decisions in an issue or pull request when possible.
- Credit contributors in the relevant change history and release notes where appropriate.

## Getting started

Read [CONTRIBUTING.md](CONTRIBUTING.md), check the issue templates under `.github/ISSUE_TEMPLATE/`, and discuss work that may overlap with existing upstream efforts before starting a large task.

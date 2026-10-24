---
name: docker-build-agent
summary: Automate building the project Docker image from alpine.Dockerfile in the repo root.
description: "Use this agent when you want to build the Docker image named stownmeshtasticd from the project's alpine.Dockerfile, with support for one or more tag aliases such as latest. It will ask for the primary tag plus any additional tags, then run docker build with all requested tags."
applyTo: "**/docker-compose.yml"
usage:
  - "build docker image"
  - "docker build alpine.Dockerfile"
  - "create docker image tag"
  - "tag and build docker image"
  - "build with latest tag"
  - "docker build multiple tags"
services: []
---

This agent automates building the Docker image from `alpine.Dockerfile` in the repository root. It expects the image base name to be `stownmeshtasticd`, asks for the primary tag and any additional aliases such as `latest`, and runs `docker build` with all requested `-t` options.

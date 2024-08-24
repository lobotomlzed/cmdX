# cmdX

[![yea](https://skillicons.dev/icons?i=cpp,neovim,linux)](https://skillicons.dev)

**cmdX** is a lightweight, console-based tool designed to capture screenshots and upload them based on ShareX `.sxcu` configuration files. I created this tool due to the lack of native support for ShareX on Linux.

## Requires:
- `libcurl`
- `libjsoncpp`

## Usage:
- `./cmdX [config.sxcu]` – Captures a screenshot and uploads it using the provided configuration file.
- `./cmdX` – Captures a screenshot and saves it locally.

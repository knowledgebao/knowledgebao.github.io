---
layout: post
title: settings-zs
date: 2019-08-05 09:50:40
description: settings-zs
tag: vscode

---

{
    // #### base config ####
    "files.autoGuessEncoding": true,
    "files.autoSave": "afterDelay",
    "files.encoding": "utf8",
    "files.eol": "\n",
    "files.exclude": {
        "**/node_modules/": true,
        "**/.git/":true,
        "**/ipch/":true,
    },
    "editor.minimap.renderCharacters": false,
    "editor.minimap.enabled": false,
    "editor.formatOnSave": false,
    "explorer.confirmDelete": false,
    "explorer.confirmDragAndDrop": false,
    "diffEditor.ignoreTrimWhitespace": true,
    "window.zoomLevel": 0,
    // #### go lang ####
    "[go]": {
        "editor.insertSpaces": false,
        "editor.formatOnSave": true,
        "editor.tabSize": 4,
    },
    "go.inferGopath": true,
    "go.toolsGopath": "C:/work/gotools",
    "go.buildOnSave": "package",
    "go.lintOnSave": "off",
    "go.vetOnSave": "package",
    "go.buildFlags": [],
    "go.vetFlags": [],
    "go.useCodeSnippetsOnFunctionSuggest": false,
    // "go.formatTool": "goreturns",
    "go.goroot": "C:/work/local/go",
    "go.gopath": "C:/work/gopath",
    // "go.lintTool": "gometalinter",
    "go.lintFlags": [
        "--config=~/.gometalinter"
    ],
    // "go.docsTool": "gogetdoc",
    // #### terminal ######
    // -- bash --
    "terminal.integrated.shell.windows": "C:/msys64/usr/bin/bash.exe",
    "terminal.integrated.shellArgs.windows": [
        "--login"
    ],
    "terminal.integrated.env.windows": {
        "MSYSTEM": "MINGW64",
        "MSYS2_PATH_TYPE": "inherit",
        "CHERE_INVOKING": "enabled_from_arguments"
    },
    // -- cmd --
    // "terminal.integrated.shell.windows": "C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe",
    // #### java ####
    // "java.home": "C:\\Program Files\\Java\\jdk1.8.0_161",
    // #### python ####
    // add C:\msys64\home\Administrator/.local/bin to PATH
    "python.pythonPath": "python3",
    "python.linting.enabled": true,
    "python.globalModuleInstallation": true,
    // #### C/C++  ####
    // ---- clang format ----
    "C_Cpp.clang_format_style": "file",
    "C_Cpp.clang_format_fallbackStyle": "{BasedOnStyle: LLVM, IndentWidth: 4, ColumnLimit: 0, AccessModifierOffset: -4}",
    "C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",
    "C_Cpp.configurationWarnings": "Disabled",
    // ---- cmake generator ----
    "cmake.cmakePath": "C:/work/scripts/vscode-cmake.bat",
    "cmake.configureOnOpen": false,
    "C_Cpp.updateChannel": "Insiders",
    "breadcrumbs.enabled": true,
    // "cmake.useCMakeServer": false,
    //  "cmake.generator": "MSYS Makefiles", // select from cmake-kits.json
}
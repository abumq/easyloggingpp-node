//
// Copyright 2017-present Muflihun Labs
//
// Part of residue-node
//
// Author: @abumusamq
//
// https://muflihun.com
// https://muflihun.github.io/residue
// https://github.com/muflihun/residue-node
// https://github.com/muflihun/residue-node-native
//

const fs = require('fs');
const path = require('path');

"use strict";

// Get location of callstack in <file>:<line> format
const getSourceLocation = (splitChar, baseIdx) => {
    const er = new Error;
    const item = er.stack.split('\n')[baseIdx || 4];
    if (!item) {
        return ['<anonymous>', 0];
    }
    return item.replace(' at ', '').trim().split(splitChar);
};

// Get file of callstack.
// See getSourceLocation
exports.getSourceFile = (baseIdx) => getSourceLocation(':', baseIdx)[0];

// Get line of callstack.
// See getSourceLocation
exports.getSourceLine = (baseIdx) => parseInt(getSourceLocation(':', baseIdx)[1]);

// Get func of call stack
// See getSourceLocation
exports.getSourceFunc = (baseIdx) => {
    const parts = getSourceLocation(' ', baseIdx);
    if (parts.length <= 1) {
        return 'anonymous';
    }
    return parts[0];
}

exports.confJson = (jsonOrFilename) => {
    if (typeof jsonOrFilename === 'object') {
        return JSON.stringify(jsonOrFilename)
    } else if (typeof jsonOrFilename === 'string' && jsonOrFilename.length > 0) {
        if (jsonOrFilename.trim()[0] === '{') {
            return jsonOrFilename.trim();
        }
        return fs.readFileSync(path.resolve(jsonOrFilename), 'utf8');
    }
    return false;
}

// Various logging levels accepted by the server
exports.LoggingLevels = {
  Trace: 2,
  Debug: 4,
  Fatal: 8,
  Error: 16,
  Warning: 32,
  Verbose: 64,
  Info: 128
};

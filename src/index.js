//
// Copyright 2017-present Muflihun Labs
//
// This module provides bridge to use C++ client library
// to handle the connection and conversation with the server
//
// Author: @abumusamq
//
// https://muflihun.com
// https://muflihun.github.io/residue
// https://github.com/muflihun/residue-node
// https://github.com/muflihun/residue-node-native
//

"use strict";

const util = require('util');
const easyloggingpp = require('bindings')('easyloggingpp');
const CommonUtils = require('./common');

const Logger = function(id) {
    this.id = id;

    easyloggingpp.register_logger(this.id);

    this.trace = (fmt, ...args)           => this._write_log(CommonUtils.LoggingLevels.Trace, undefined, fmt, ...args);
    this.debug = (fmt, ...args)           => this._write_log(CommonUtils.LoggingLevels.Debug, undefined, fmt, ...args);
    this.fatal = (vlevel, fmt, ...args)   => this._write_log(CommonUtils.LoggingLevels.Fatal, vlevel, fmt, ...args);
    this.error = (fmt, ...args)           => this._write_log(CommonUtils.LoggingLevels.Error, undefined, fmt, ...args);
    this.warn = (fmt, ...args)            => this._write_log(CommonUtils.LoggingLevels.Warning, undefined, fmt, ...args);
    this.verbose = (vlevel, fmt, ...args) => this._write_log(CommonUtils.LoggingLevels.Verbose, vlevel, fmt, ...args);
    this.info = (fmt, ...args)            => this._write_log(CommonUtils.LoggingLevels.Info, undefined, fmt, ...args);

    // private members

    this._source_base_index = 5;
    this._write_log = (level, vlevel, fmt, ...args) => {
        const cpy = args;
        for (var idx = 0; idx < cpy.length; ++idx) {
            if (typeof cpy[idx] === 'object') {
                cpy[idx] = JSON.stringify(cpy[idx]);
            }
        }

        easyloggingpp.write_log(this.id,
                                this.log_sources.getSourceFile(),
                                this.log_sources.getSourceLine(),
                                this.log_sources.getSourceFunc(),
                                util.format(fmt, ...cpy),
                                level,
                                vlevel);
    }

    this.log_sources = {
        base_idx: 6,
        getSourceFile: () => CommonUtils.getSourceFile(this.log_sources.base_idx),
        getSourceLine: () => CommonUtils.getSourceLine(this.log_sources.base_idx),
        getSourceFunc: () => CommonUtils.getSourceFunc(this.log_sources.base_idx),
    };

    this.configure = (conf) => {
        if (typeof conf !== 'object') {
            throw new Error(`Invalid [${typeof conf} type. Configuration must be object`);
        }
        if (conf.config_file) {
            easyloggingpp.configure_from_file(this.id, conf.config_file);
            return;
        }
        if (conf.config && conf.value) {
            easyloggingpp.configure(this.id, conf.config, conf.value);
        }

        if (Array.isArray(conf)) {
            conf.forEach(c => (item) => {
                this.configure(item);
            })
        }
    };
};

const configureAllLoggers = (conf) => {
    if (typeof conf !== 'object') {
        throw new Error(`Invalid [${typeof conf} type. Configuration must be object`);
    }
    if (conf.config_file) {
        easyloggingpp.configure_all_loggers_from_file(conf.config_file);
        return;
    }
    if (conf.level && conf.config && conf.value) {
        easyloggingpp.configure_all_loggers_by_level(conf.level, conf.config, conf.value);
        return;
    }
    if (conf.config && conf.value) {
        easyloggingpp.configure_all_loggers(conf.config, conf.value);
        return;
    }

    if (Array.isArray(conf)) {
        conf.forEach(c => (item) => {
            configureAllLoggers(item);
        })
    }
};

exports.version = easyloggingpp.version;
exports.getLogger = (id) => (new Logger(id));
exports.configureAllLoggers = configureAllLoggers;
exports.Level = CommonUtils.LoggingLevels;
exports.ConfigType = CommonUtils.ConfigurationType;

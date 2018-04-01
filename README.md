﷽

# Easylogging++ Node.js Binding

[![Build Status](https://img.shields.io/travis/muflihun/easyloggingpp-node/master.svg)](https://travis-ci.org/muflihun/easyloggingpp-node/branches)
[![Build status](https://ci.appveyor.com/api/projects/status/sfcgrehu8ypkrun3?svg=true)](https://ci.appveyor.com/project/abumusamq/easyloggingpp-node)

[![Version](https://img.shields.io/npm/v/easyloggingpp.svg)](https://www.npmjs.com/package/easyloggingpp)

[![GitHub license](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/muflihun/easyloggingpp-node/blob/master/LICENSE)
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/MuflihunDotCom/25)

Easylogging++ Node.js binding provides ability to use efficient [Easylogging++](https://github.com/muflihun/easyloggingpp) to log important logs for your application.

## Download
```
npm install --save easyloggingpp
```

## Getting Started
```js
const easyloggingpp = require('easyloggingpp');
const ConfigType = easyloggingpp.ConfigType;
const Level = easyloggingpp.Level;
const logger = easyloggingpp.getLogger('mylogger'); // register logger

easyloggingpp.configureAllLoggers([
    {
        config: ConfigType.Format,
        value: '%levshort %datetime %fbase:%line %msg',  // <-- fbase or file for full path 
    },
    {
        config: ConfigType.Filename,
        value: 'logs/output.log'
    }
]);

// alternatively you can use following to set default configurations
// for future loggers as well as existing logger
easyloggingpp.configureAllLoggers({
    config_file: 'easylogging-config.conf',
});

logger.info('simple log');
logger.info('array %s', [1, 2, 3]);
var person = { 'name': 'Adam', 'age': 960, }
logger.info('obj %s', person);

logger.error('an error occurred %s', new Error("error msg"));

easyloggingpp.setLogErrorStack(false); // turn stack logging off
logger.fatal('serious error occurred %s', new Error("fatal msg"));
logger.error('an error occurred %s', new Error("error msg"));
```

Above will print something like:
![sample-output]

## Log
```js
logger.info(...);
logger.warn(...);
logger.error(...);
logger.debug(...);
logger.trace(...);
logger.fatal(...);
logger.verbose(verbose_level, ...);
```

## Log Formats
You can use advanced logging format specifiers. 

```
logger.info('array %s', [1, 2, 3]);
```

Taken from [utils.format](https://nodejs.org/docs/latest/api/util.html#util_util_format_format_args)

| Format specifier | Explanation |
|----|-----|
| %s | String. |
| %d | Number (integer or floating point value). |
| %i | Integer. |
| %f | Floating point value. |
| %j | JSON. Replaced with the string '[Circular]' if the argument contains circular references. |
| %% | single percent sign ('%'). This does not consume an argument. |

`%o` and `%O` should not be used. Use `%s` instead for better output.

## Global Configuration
### [via File](https://github.com/muflihun/easyloggingpp#using-configuration-file)
```js
easyloggingpp.configureAllLoggers({
    config_file: 'easylogging-config.conf',
});
```

This will configure all the existing loggers and set this new configuation to default for future loggers.

### All Levels
```js
easyloggingpp.configureAllLoggers({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```js
easyloggingpp.configureAllLoggers([
  {
      config: easyloggingpp.ConfigType.Format,
      value: '%datetime %msg',
  },
  {
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %file:%line %msg',
  }
]);
```

This will configure existing loggers but will not change future loggers.

### Specific Level
```js
easyloggingpp.configureAllLoggers({
    level: easyloggingpp.Level.Info,
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```js
easyloggingpp.configureAllLoggers([
  {
      level: easyloggingpp.Level.Info,
      config: easyloggingpp.ConfigType.Format,
      value: '%datetime %msg',
  },
  {
    level: easyloggingpp.Level.Debug,
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %file:%line %msg',
  }
]);
```
This will configure existing loggers but will not change future loggers.

## Logger Configuration
### [via File](https://github.com/muflihun/easyloggingpp#using-configuration-file)
```js
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config_file: 'easylogging-config.conf',
});
```

### All Levels
```js
const logger = easyloggingpp.getLogger('logger1');

logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```js
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```

### Specific Level
```js
const logger = easyloggingpp.getLogger('logger1');

logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```js
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```

This will configure existing loggers but will not change future loggers.

## Add/Remove [Logging Flag](https://github.com/muflihun/easyloggingpp#logging-flags)
```js
easyloggingpp.addFlag(easyloggingpp.LoggingFlag.ColoredTerminalOutput);
easyloggingpp.removeFlag(easyloggingpp.LoggingFlag.ColoredTerminalOutput);
```


## Profiler
You can use built-in profiler
```js
logger.startProfiling('profiling-id');
// some heavy task
for (var i = 0; i < 100000; ++i) {
    
}
logger.endProfiling('profiling-id');

// other tasks that will not be profiled
// if needed or you could use finishProfiling directly

logger.finishProfiling('profiling-id', (item) => {
    logger.info(`finished profiling in ${item.diff}ms`);
});
```

## Notes
Some notes for those who have previous experience with Easylogging++ (and for those who are absolutely new)

* Logs are written to `/dev/null` by default. You must configure via `easyloggingpp.configureAllLoggers` at initialization.
* Loggers are created automatically when you use `easyloggingpp.getLogger`.
* `ColoredTerminalOutput` flag is set by default. You can unset it using `easyloggingpp.removeFlag`
* You can safely log with `Fatal` level as `DisableApplicationAbortOnFatalLog` flag is set by default. You should not remove this flag. [Read more](https://github.com/muflihun/easyloggingpp#logging-flags)

## License
```
Copyright 2017-present Muflihun Labs
Copyright 2017-present @abumusamq

https://github.com/muflihun/
https://muflihun.github.io/
https://muflihun.com/

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```

  [sample-output]: https://github.com/muflihun/easyloggingpp-node/raw/master/rc/output.png



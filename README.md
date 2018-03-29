﷽

# Easylogging++ Node.js Binding

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



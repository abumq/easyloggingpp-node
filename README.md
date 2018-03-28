﷽

# Easylogging++ Node.js Binding

[![Version](https://img.shields.io/npm/v/easyloggingpp.svg)](https://www.npmjs.com/package/easyloggingpp)
[![GitHub license](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/muflihun/easyloggingpp-node/blob/master/LICENSE)
[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.me/MuflihunDotCom/25)

Easylogging++ Node.js binding provides ability to use efficient [Easylogging++](https://github.com/muflihun/easyloggingpp) to log important logs for your application.

## Getting Started
```
const easyloggingpp = require('easyloggingpp');

const logger = easyloggingpp.getLogger('logger1');

logger.info('simple log');

logger.info('array %s', [1, 2, 3]);

var person = { 'name': 'Adam', 'age': 960, }
logger.info('obj %s', person);

logger.info('null %s', null);

logger.info('undefined %s', undefined);

// other levels
logger.warn(...);
logger.error(...);
logger.debug(...);
logger.trace(...);
logger.fatal(...);
logger.verbose(verbose-level, ...);
```

## Global Configuration
### [via File](https://github.com/muflihun/easyloggingpp#using-configuration-file)
```
easyloggingpp.configureAllLoggers({
    config_file: 'easylogging-config.conf',
});
```

This will configure all the existing loggers and set this new configuation to default for future loggers.

### All Levels
```
easyloggingpp.configureAllLoggers({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```
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
```
easyloggingpp.configureAllLoggers({
    level: easyloggingpp.Level.Info,
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```
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
```
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config_file: 'easylogging-config.conf',
});
```

### All Levels
```
const logger = easyloggingpp.getLogger('logger1');

logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```

### Specific Level
```
const logger = easyloggingpp.getLogger('logger1');

logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```
**or using array**
```
const logger = easyloggingpp.getLogger('logger1');
logger.configure({
    config: easyloggingpp.ConfigType.Format,
    value: '%datetime %msg',
});
```

This will configure existing loggers but will not change future loggers.

## Add/Remove [Logging Flag](https://github.com/muflihun/easyloggingpp#logging-flags)
```
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

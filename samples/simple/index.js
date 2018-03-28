const easyloggingpp = require('easyloggingpp');

const logger = easyloggingpp.getLogger('mylogger');

logger.configure({
    config_file: 'default.conf'
});

logger.info('info log');

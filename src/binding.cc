//
//  binding.cc
//  Easylogging++ Node.js Binding
//
//  Copyright (C) 2017-present Muflihun Labs
//  Copyright (C) 2017-present @abumusamq
//
//  https://muflihun.com/
//  https://github.com/muflihun/easyloggingpp-node/
//
//  See https://github.com/muflihun/easyloggingpp-node/blob/master/LICENSE
//  for licensing information
//

#include <nan.h>
#include <easylogging++.h>

using v8::FunctionTemplate;
using v8::Isolate;
using v8::String;
using Nan::To;
using Nan::GetFunction;
using Nan::New;
using Nan::Set;

INITIALIZE_EASYLOGGINGPP

NAN_METHOD(Version)
{
    info.GetReturnValue().Set(String::NewFromUtf8(Isolate::GetCurrent(), el::VersionInfo::version().c_str()));
}

NAN_METHOD(AddFlag)
{
    const std::string flag = *Nan::Utf8String(info[0]);

    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    el::Loggers::addFlag(loggingFlag);
}

NAN_METHOD(RemoveFlag)
{
    const std::string flag = *Nan::Utf8String(info[0]);

    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    el::Loggers::removeFlag(loggingFlag);
}

NAN_METHOD(HasFlag)
{
    const std::string flag = *Nan::Utf8String(info[0]);

    el::LoggingFlag loggingFlag(static_cast<el::LoggingFlag>(stoi(flag)));

    bool has = el::Loggers::hasFlag(loggingFlag);

    info.GetReturnValue().Set(has ? Nan::True() : Nan::False());
}

NAN_METHOD(RegisterLogger)
{
    const std::string loggerId = *Nan::Utf8String(info[0]);
    
    if (!el::Logger::isValidId(loggerId)) {
        return Nan::ThrowError(Nan::Error("Invalid logger ID. Allowed characters are alpha-numeric, hyphen, underscore or dot"));
    }
    el::Loggers::getLogger(loggerId, true);
}

NAN_METHOD(ConfigureFromFile)
{
    const std::string loggerId = *Nan::Utf8String(info[0]);
    const std::string file = *Nan::Utf8String(info[1]);

    el::Configurations conf(file);
    el::Logger* logger = el::Loggers::getLogger(loggerId, true);
    el::Loggers::reconfigureLogger(logger, conf);
}

NAN_METHOD(ConfigureValue)
{
    const std::string loggerId = *Nan::Utf8String(info[0]);
    const std::string configType = *Nan::Utf8String(info[1]);
    const std::string value = *Nan::Utf8String(info[2]);

    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Logger* logger = el::Loggers::getLogger(loggerId, true);
    el::Loggers::reconfigureLogger(logger->id(), config, value);
}

NAN_METHOD(ConfigureAllFromFile)
{
    const std::string file = *Nan::Utf8String(info[0]);

    el::Configurations conf(file);
    el::Loggers::setDefaultConfigurations(conf, true);
}

NAN_METHOD(ConfigureAllValue)
{
    const std::string configType = *Nan::Utf8String(info[0]);
    const std::string value = *Nan::Utf8String(info[1]);

    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Loggers::reconfigureAllLoggers(config, value);
}

NAN_METHOD(ConfigureAllValueByLevel)
{
    const std::string levelType = *Nan::Utf8String(info[0]);
    const std::string configType = *Nan::Utf8String(info[1]);
    const std::string value = *Nan::Utf8String(info[2]);

    el::Level level(static_cast<el::Level>(stoi(levelType)));
    el::ConfigurationType config(static_cast<el::ConfigurationType>(stoi(configType)));
    el::Loggers::reconfigureAllLoggers(level, config, value);
}

NAN_METHOD(WriteLog) {
    const std::string loggerId = *Nan::Utf8String(info[0]);
    const std::string file = *Nan::Utf8String(info[1]);
    const std::string func = *Nan::Utf8String(info[3]);
    const std::string msg = *Nan::Utf8String(info[4]);
    std::string level = "128";
    std::string line = "0";
    std::string vlevel = "0";
    
    if (info[5]->IsNumber()) {
        level = *Nan::Utf8String(info[5]);
    }
    if (info[2]->IsNumber()) {
        line = *Nan::Utf8String(info[2]);
    }
    if (info[6]->IsNumber()) {
        vlevel = *Nan::Utf8String(info[6]);
    }

    el::base::type::LineNumber lineNumb = stoi(line);
    el::Level lvl = static_cast<el::Level>(stoi(level));
    el::base::type::VerboseLevel vl = stoi(vlevel);

    el::base::Writer(lvl,
                     file.c_str(),
                     lineNumb, func.c_str(),
                     el::base::DispatchAction::NormalLog, vl)
    .construct(1, loggerId.c_str()) << msg;
}

NAN_MODULE_INIT(InitAll)
{
    el::Loggers::addFlag(el::LoggingFlag::DisableApplicationAbortOnFatalLog);
    el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
    el::Loggers::addFlag(el::LoggingFlag::AllowVerboseIfModuleNotSpecified);

    #define DEFINE_FN(name, callback) Set(target, New<String>(#name).ToLocalChecked(), \
        GetFunction(New<FunctionTemplate>(callback)).ToLocalChecked())

    DEFINE_FN(version, Version);
    DEFINE_FN(configure_from_file, ConfigureFromFile);
    DEFINE_FN(configure, ConfigureValue);
    DEFINE_FN(configure_all_loggers_from_file, ConfigureAllFromFile);
    DEFINE_FN(configure_all_loggers, ConfigureAllValue);
    DEFINE_FN(configure_all_loggers_by_level, ConfigureAllValueByLevel);
    DEFINE_FN(write_log, WriteLog);
    DEFINE_FN(register_logger, RegisterLogger);
    DEFINE_FN(add_flag, AddFlag);
    DEFINE_FN(remove_flag, RemoveFlag);
    DEFINE_FN(has_flag, HasFlag);
    #undef DEFINE_FN
}


NODE_MODULE(easyloggingpp, InitAll)

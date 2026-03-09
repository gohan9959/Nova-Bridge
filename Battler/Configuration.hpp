#pragma once
#include <string>
class Configuration {
    private:
        std::string commandFilePath;
        std::string gameConfigFilePath;
        std::string scriptStatusFilePath;
        std::string pokemonFilePath;
        std::string itemFilePath;
        std::string logFilePath;
        std::string pokemonDataFilePath;
        std::string itemDataFilePath;
        std::string moveDataFilePath;
    public:
        Configuration(const std::string& commandFile, const std::string& gameConfigFile, const std::string& scriptStatusFile, const std::string& pokemonFilePath, const std::string& itemFilePath, const std::string& logFilePath, const std::string& pokemonDataFilePath, const std::string& itemDataFilePath, const std::string& moveDataFilePath)
            : commandFilePath(commandFile), gameConfigFilePath(gameConfigFile), scriptStatusFilePath(scriptStatusFile), pokemonFilePath(pokemonFilePath), itemFilePath(itemFilePath), logFilePath(logFilePath), pokemonDataFilePath(pokemonDataFilePath), itemDataFilePath(itemDataFilePath), moveDataFilePath(moveDataFilePath) {};
        const std::string& getCommandFilePath() const{return commandFilePath;};
        const std::string& getGameConfigFilePath() const{return gameConfigFilePath;};
        const std::string& getScriptStatusFilePath() const{return scriptStatusFilePath;};
        const std::string& getPokemonFilePath() const{return pokemonFilePath;};
        const std::string& getItemFilePath() const{return itemFilePath;};
        const std::string& getLogFilePath() const{return logFilePath;};
        const std::string& getPokemonDataFilePath() const{return pokemonDataFilePath;};
        const std::string& getItemDataFilePath() const{return itemDataFilePath;};
        const std::string& getMoveDataFilePath() const{return moveDataFilePath;};
};
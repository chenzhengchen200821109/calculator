#include "serialize.h"
#include "commandParser.h"

const long Version = 1;

CommandParser::CommandParser(Scanner& scanner, Calculator& calc) : _scanner(scanner), _calc(calc)
{
    assert(_scanner.IsCommand());
    _scanner.Accept();
    std::string name = _scanner.GetSymbolName();
    switch(name[0])
    {
        case 'q':
        case 'Q':
            _command = comQuit;
            break;
        case 's':
        case 'S':
            _command = comSave;
            break;
        case 'l':
        case 'L':
            _command = comLoad;
            break;
        default:
            _command = comError;
            break;
    }
}

Status CommandParser::Execute()
{
    _scanner.AcceptCommand();
    std::string nameFile;
    switch(_command)
    {
        case comSave:
            nameFile = _scanner.GetSymbolName();
            return Save(nameFile);
        case comLoad:
            nameFile = _scanner.GetSymbolName();
            return Load(nameFile);
        case comQuit:
            std::cerr << "GoodBye!" << std::endl;
            return stQuit; // quit
        case comError:
            std::cerr << "Error" << std::endl;
            return stError;
    }
    return stOk; // continue on a loop
}

Status CommandParser::Save(std::string const& fileName)
{
    std::cerr << "Save to: \"" << fileName << "\"\n";
    Status status = stOk;
    try 
    {
        Serializer out(fileName);
        out.PutLong(Version);
        _calc.Serialize(out);
    }
    catch(char const * msg)
    {
        std::cerr << "Error: Save failed: " << msg << std::endl;
        status = stError;
    }
    catch(...)
    {
        std::cerr << "Error: Save failed\n";
        throw; // re-throw
    }
    return status;
}

Status CommandParser::Load(std::string const& fileName)
{
    std::cerr << "Load from: \"" << fileName << "\"\n";
    Status status = stOk;
    try
    {
        DeSerializer in(fileName);
        long ver = in.GetLong();
        if (ver != Version)
            throw "Version number mismatch";
        _calc.DeSerialize(in);
    }
    catch(char const * fileName)
    {
        std::cerr << "Error: Load failed:" << std::endl;
        status = stError;
    }
    catch(...)
    {
        std::cerr << "Error: Load failed\n";
        throw;
    }
    return status;
}

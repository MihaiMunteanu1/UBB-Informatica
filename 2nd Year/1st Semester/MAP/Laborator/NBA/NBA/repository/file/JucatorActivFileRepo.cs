using NBA.domain;

namespace NBA.repository.file;

public class JucatorActivFileRepo(string filePath)
    : FileRepository<int, JucatorActiv>(filePath, stringToEntity, entityToString)
{
    public static JucatorActiv stringToEntity(string line)
    {
        var tokens = line.Split(',');
        var id = int.Parse(tokens[0]);
        var idPlayer = int.Parse(tokens[1]);
        var idGame = int.Parse(tokens[2]);
        var nrPoints = int.Parse(tokens[3]);
        var type = Enum.Parse<Tip>(tokens[4]);        
        return new JucatorActiv{Id = id, IdPlayer = idPlayer,IdGame = idGame,NrPoints = nrPoints,Type = type};
    }

    public static string entityToString(JucatorActiv jucatorActiv)
    {
        return jucatorActiv.Id + ',' + jucatorActiv.IdPlayer + ',' + jucatorActiv.IdGame + ',' + 
               jucatorActiv.NrPoints + ',' + jucatorActiv.Type.ToString();
    }

}
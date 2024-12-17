using NBA.domain;

namespace NBA.repository.file;

public class JucatorActivFileRepo : FileRepository<int,JucatorActiv>
{
    public JucatorActivFileRepo(string filePath) : base(filePath, stringToEntity, entityToString)
    {
    }
    public static JucatorActiv stringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        int idPlayer = int.Parse(tokens[1]);
        int idGame = int.Parse(tokens[2]);
        int nrPoints = int.Parse(tokens[3]);
        Tip type = Enum.Parse<Tip>(tokens[4]);        
        return new JucatorActiv{id = id, idPlayer = idPlayer,idGame = idGame,nrPoints = nrPoints,Type = type};
    }

    public static string entityToString(JucatorActiv jucatorActiv)
    {
        return jucatorActiv.id + ',' + jucatorActiv.idPlayer + ',' + jucatorActiv.idGame + ',' + 
               jucatorActiv.nrPoints + ',' + jucatorActiv.Type.ToString();
    }

}
using NBA.domain;

namespace NBA.repository.file;

public class EchipaFileRepo(string filePath) : FileRepository<int, Echipa>(filePath, stringToEntity, entityToString)
{
    public static Echipa stringToEntity(string line)
    {
        var tokens = line.Split(',');
        var id = int.Parse(tokens[0]);
        var nume = tokens[1];
        return new Echipa{Id = id, Name = nume};
    }

    public static string entityToString(Echipa echipa)
    {
        return echipa.Id + ',' + echipa.Name;
    }
}
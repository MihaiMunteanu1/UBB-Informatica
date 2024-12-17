using NBA.domain;

namespace NBA.repository.file;

public class EchipaFileRepo : FileRepository<int, Echipa>
{
    public EchipaFileRepo(string filePath) : base(filePath, stringToEntity, entityToString)
    {
    }

    public static Echipa stringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        string nume = tokens[1];
        return new Echipa{id = id, Name = nume};
    }

    public static string entityToString(Echipa echipa)
    {
        return echipa.id + ',' + echipa.Name;
    }
}
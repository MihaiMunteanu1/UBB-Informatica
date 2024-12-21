using NBA.domain;

namespace NBA.repository.file;

public class ElevFileRepo(string filePath) : FileRepository<int, Elev>(filePath, stringToEntity, entityToString)
{
    public static Elev stringToEntity(string line)
    {
        var tokens = line.Split(',');
        var id = int.Parse(tokens[0]);
        var name = tokens[1];
        var school = tokens[2];
        return new Elev{Id = id, Name = name, School = school};
    }

    public static string entityToString(Elev elev)
    {
        return elev.Id + ',' + elev.Name + ',' + elev.School;
    }
}
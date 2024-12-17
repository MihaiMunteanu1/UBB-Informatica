using NBA.domain;

namespace NBA.repository.file;

public class ElevFileRepo : FileRepository<int,Elev>
{
    public ElevFileRepo(string filePath) : base(filePath, stringToEntity, entityToString)
    {
    }
    public static Elev stringToEntity(string line)
    {
        string[] tokens = line.Split(',');
        int id = int.Parse(tokens[0]);
        string name = tokens[1];
        string school = tokens[2];
        return new Elev{id = id, Name = name, School = school};
    }

    public static string entityToString(Elev elev)
    {
        return elev.id + ',' + elev.Name + ',' + elev.School;
    }
}
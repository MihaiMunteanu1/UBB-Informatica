using NBA.domain;

namespace NBA.repository.file;

public class MeciFileRepo : FileRepository<int,Meci>
{
    private readonly IRepository<int, Echipa> echipe;
    
    public MeciFileRepo(string filePath,IRepository<int, Echipa> echipee) : 
        base(filePath, line => stringToEntity(line,echipee), entityToString)
    {
        echipe = echipee;
    }
    public static Meci stringToEntity(string line, IRepository<int, Echipa> echipee)
    {
        string[] tokens = line.Split(',');
        if (tokens.Length < 4 || !int.TryParse(tokens[0], out int id) || !DateTime.TryParseExact(tokens[3], "dd/MM/yyyy", null, System.Globalization.DateTimeStyles.None, out DateTime date))
        {
            throw new FormatException("The input string is not in the correct format.");
        }

        Echipa echipa1 = echipee.FindOne(int.Parse(tokens[1]));
        Echipa echipa2 = echipee.FindOne(int.Parse(tokens[2]));

        return new Meci { id = id, Team1 = echipa1, Team2 = echipa2, Date = date };
    }

    public static string entityToString(Meci meci)
    {
        return $"{meci.id},{meci.Team1.id},{meci.Team2.id},{meci.Date:dd/MM/yyyy}";
    }
}
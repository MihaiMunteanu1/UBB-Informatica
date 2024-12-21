using NBA.domain;

namespace NBA.repository.file;

public class MeciFileRepo(string filePath, IRepository<int, Echipa> echipee)
    : FileRepository<int, Meci>(filePath, line => stringToEntity(line, echipee), entityToString)
{

    public static Meci stringToEntity(string line, IRepository<int, Echipa> echipee)
    {
        string[] tokens = line.Split(',');
        if (tokens.Length < 4 || !int.TryParse(tokens[0], out var id) || !DateTime.TryParseExact(tokens[3], "dd/MM/yyyy", null, System.Globalization.DateTimeStyles.None, out var date))
        {
            throw new FormatException("The input string is not in the correct format.");
        }

        var echipa1 = echipee.FindOne(int.Parse(tokens[1])) ?? throw new InvalidOperationException();
        var echipa2 = echipee.FindOne(int.Parse(tokens[2])) ?? throw new InvalidOperationException();

        return new Meci { Id = id, Team1 = echipa1, Team2 = echipa2, Date = date };
    }

    public static string entityToString(Meci meci)
    {
        return $"{meci.Id},{meci.Team1.Id},{meci.Team2.Id},{meci.Date:dd/MM/yyyy}";
    }
}
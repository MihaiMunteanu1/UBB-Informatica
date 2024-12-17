using NBA.domain;

namespace NBA.repository.file;

public class JucatorFileRepo : FileRepository<int,Jucator>
{

    private readonly IRepository<int, Echipa> _echipe;
    public JucatorFileRepo(string filePath,IRepository<int, Echipa> echipe) : 
        base(filePath,line => stringToEntity(line,echipe), entityToString)
    {
        _echipe = echipe ?? throw new ArgumentNullException(nameof(echipe));
    }
    public static Jucator stringToEntity(string line, IRepository<int, Echipa> echipe)
    {
        string[] tokens = line.Split(',');
        if (tokens.Length < 4) 
        {
            throw new FormatException("The input string is not in the correct format.");
        }

        if (!int.TryParse(tokens[0], out int id))
        {
            throw new FormatException("The input string is not in the correct format.22");
        }

        if (!int.TryParse(tokens[3], out int idE))
        {
            throw new FormatException("The input string is not in the correct format.333");
        }
        string nume = tokens[1];
        string scoala = tokens[2];
        Echipa echipa = echipe.FindOne(idE);
        if (echipa == null)
        {
            throw new Exception($"Echipa with ID {idE} not found.");
        }
        return new Jucator { id = id, Name = nume, School = scoala, Team = echipa };
    }

    public static string entityToString(Jucator jucator)
    {
        return jucator.id + ',' + jucator.Name + ',' + jucator.School + ',' + jucator.Team;
    }

}
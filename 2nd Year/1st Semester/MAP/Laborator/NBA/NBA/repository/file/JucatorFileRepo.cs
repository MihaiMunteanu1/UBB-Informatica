using NBA.domain;

namespace NBA.repository.file;

public class JucatorFileRepo(string filePath, IRepository<int, Echipa> echipe)
    : FileRepository<int, Jucator>(filePath, line => stringToEntity(line, echipe), entityToString)
{
    
    public static Jucator stringToEntity(string line, IRepository<int, Echipa> echipe)
    {
        var tokens = line.Split(',');
        if (tokens.Length < 4) 
        {
            throw new FormatException("The input string is not in the correct format.");
        }

        if (!int.TryParse(tokens[0], out var id))
        {
            throw new FormatException("The input string is not in the correct format.22");
        }

        if (!int.TryParse(tokens[3], out var idE))
        {
            throw new FormatException("The input string is not in the correct format.333");
        }
        var nume = tokens[1];
        var scoala = tokens[2];
        var echipa = echipe.FindOne(idE);
        if (echipa == null)
        {
            throw new Exception($"Echipa with ID {idE} not found.");
        }
        return new Jucator { Id = id, Name = nume, School = scoala, Team = echipa };
    }

    public static string entityToString(Jucator jucator)
    {
        return jucator.Id + ',' + jucator.Name + ',' + jucator.School + ',' + jucator.Team;
    }

}
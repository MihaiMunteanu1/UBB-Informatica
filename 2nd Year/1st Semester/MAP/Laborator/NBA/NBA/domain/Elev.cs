namespace NBA.domain;

public class Elev : Entity<int>
{
    private string name { init; get; }
    private string school { init; get; }
    
    public string Name
    {
        get => name;
        init => name = value;
    }
    public string School
    {
        get => school;
        init => school = value;
    }

    public override string ToString()
    {
        return $"{nameof(name)}: {name}, {nameof(school)}: {school}";
    }
}
namespace NBA.domain;

public class Elev : Entity<int>
{
    private string name { set; get; }
    private string school { set; get; }
    
    public string Name
    {
        get
        {
            return name;
        }
        set
        {
            name = value;
        }
    }
    public string School
    {
        get
        {
            return school;
        }
        set
        {
            school = value;
        }
    }

    public override string ToString()
    {
        return $"{nameof(name)}: {name}, {nameof(school)}: {school}";
    }
}
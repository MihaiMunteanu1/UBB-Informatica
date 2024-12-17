namespace Lab9.model;

public abstract class Task
{
    private string Id{set;get;}
    private string Description{set;get;}

    public Task(string id, string description)
    {
        Id = id;
        Description = description;
    }

    public abstract void Execute();

    public override string ToString()
    {
        return $"{nameof(Id)}: {Id}, {nameof(Description)}: {Description}";
    }

    protected bool Equals(Task other)
    {
        return Id == other.Id && Description == other.Description;
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != GetType()) return false;
        return Equals((Task)obj);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Id, Description);
    }
    
    
}
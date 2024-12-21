using NBA.domain;
using NBA.repository.memory;

namespace NBA.repository.file;

public delegate E StringToEntity<E>(string input);
public delegate string EntityToString<E>(E entity);

public class FileRepository<ID, E> : InMemoryRepository<ID, E> where E : Entity<ID>
{
    private readonly string _filePath;
    private readonly StringToEntity<E> _stringToEntity;
    private readonly EntityToString<E> _entityToString;

    protected FileRepository(string filePath, StringToEntity<E> stringToEntity, EntityToString<E> entityToString)
    {
        _filePath = filePath;
        _stringToEntity = stringToEntity;
        _entityToString = entityToString;
        ReadFromFile();
    }

    public void ReadFromFile()
    {
        using var sr = new StreamReader(_filePath);
        while (sr.ReadLine() is { } line)
            base.Save(_stringToEntity(line));
    }

    public void WriteToFile()
    {
        using var sw = new StreamWriter(_filePath);
        foreach (var entity in base.FindAll())
            sw.WriteLine(_entityToString(entity));
    }

    public override E? Save(E entity)
    {
        var e= base.Save(entity);
        if(e != null)
            WriteToFile();
        return e;
    }
    
    public override E? Delete(ID id)
    {
        var e = base.Delete(id);
        if(e!=null)
            WriteToFile();
        return e;
    }
}
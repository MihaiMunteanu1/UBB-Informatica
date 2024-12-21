using NBA.domain;

namespace NBA.repository.memory;

public class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    private readonly Dictionary<ID, E> _entities = new();
    
    public E? FindOne(ID id)
    {
        return _entities.GetValueOrDefault(id);
    }

    public IEnumerable<E> FindAll()
    {
        return _entities.Values;
    }

    public virtual E? Save(E entity)
    {
        return _entities.TryAdd(entity.Id, entity) ? entity : null;
    }

    public virtual E? Delete(ID id)
    {
        _entities.Remove(id, out var entity);
        return entity;
    }
}
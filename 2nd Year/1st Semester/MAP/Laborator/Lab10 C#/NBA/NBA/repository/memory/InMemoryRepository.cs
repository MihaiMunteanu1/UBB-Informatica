using NBA.domain;

namespace NBA.repository.memory;

public class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    Dictionary<ID, E> _entities = new();
    
    public E? FindOne(ID id)
    {
        return _entities.ContainsKey(id) ? _entities[id] : default;
    }

    public IEnumerable<E> FindAll()
    {
        return _entities.Values;
    }

    public virtual E? Save(E entity)
    {
        return _entities.TryAdd(entity.id, entity) ? entity : null;
    }

    public virtual E? Delete(ID id)
    {
        _entities.Remove(id, out E? entity);
        return entity;
    }
}
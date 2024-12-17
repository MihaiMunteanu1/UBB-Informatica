import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID,E extends Entity<ID>> implements Repository<ID,E> {

    private Map<ID,E> entities=new HashMap<>();

    @Override
    public E findOne(ID id) {
        if(id==null)
            throw new IllegalArgumentException("ID null");
        return entities.get(id);
    }

    @Override
    public Iterable<E> findAll() {
        return entities.values();
    }

    @Override
    public E save(E entity) {
        if(entity==null)
            throw new IllegalArgumentException("Entity null");

        E existing_entitate=entities.get(entity.getId());
        if(entities.get(entity.getId())!=null)
            return existing_entitate;

        entities.put(entity.getId(), entity);
        return null;
    }

    @Override
    public E delete(ID id) {
        if(id==null)
            throw new IllegalArgumentException("ID null");

        return entities.remove(id);
    }

    @Override
    public E update(E entity) {
        if(entity==null)
            throw new IllegalArgumentException("Entity null");
        E existing_entitate=entities.get(entity.getId());
        if(entities.get(entity.getId())==null)
            return entity;
        entities.put(entity.getId(), entity);
        return null;
    }
}

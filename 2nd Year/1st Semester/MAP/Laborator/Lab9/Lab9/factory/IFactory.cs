using Lab9.model;

namespace Lab9.factory;

public interface IFactory
{
    IContainer CreateContainer(Strategy strategy);
}
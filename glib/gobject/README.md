# GObject : 기초

GObject type system 의 가장 기초 레벨에는 GType system 이 있다. 이 GType system 은 프로그래머들이 다룰수 있는 모든 가능한 타입들의 
런타임 명세를 구현하고 있다. 이 시스템은 glue 의 일종처럼 동작하는데 C code 를 다른 언어에 링킹시켜줄 수 있기 때문이다. 
(물론 이 언어는 dynamic GLib type system 를 사용해서 빌드된 라이브러리에 대한 바인딩을 지니고 있어야함. ) 

GObject type system 은 단일 상속, 캡슐화, 가상함수, C++ field 와 유사하지만 추가적인 기능들이 더 추가된 소위 property 라고 하는 것들을 지원한다. 
또, signal system 을 지원해서  event oriented 패레임워크에서 효과적이고 진보된 설계를 할 수 있다. 

GObject type system 은 세가지 entity 로 구성된다. 
- 기초적인 unmanaged type ( gchar, gpointer, gboolean 등등 ) 
- 인스턴스화 할수 있는 classified type ( C++ 의 클래스와 유사함 ) 
- 인스턴스화 할 수 없는 classfieid type  ( interface, C++ 에서는 순수추상클래스) 

```
#define OURNAMESPACE_TYPE_OUROBJECT ournamespace_ourobject_get_type()

```
위 함수는 해당 타입에 대한 모든 기본적인 정보를 담고있는 GType structure 를 반환한다. 이름, 객체에 필요한 메모리,  클래스/객체의 초기화,finalization 에 대한 함수들. (생성자/소멸자와 비슷 ) 


```
G_DECARE_DERIVABLE_TYPE (NamespaceObject, namespace_object, NAMESPACE, OBJECT, ParentClass)

```

GObject 나 GObject 를 상속하는 객체라면 두 structure 로 구성된다. 

```
struct _NamespaceObject
struct _NamespaceObjectClass
```


```

We agree to call them the actual object and class. In current versions of GObject, in general, there is no need to implement the object structure in an explicit form, often it is automatically generated as a result of expanding the macro. A class must be implemented explicitly if our goal is to build an inheritance hierarchy with redefinition of virtual functions.

GObjects are of two types, differing in the possibility of inheritance - derivable and final. In the second case, the last macro would look like G_DECLARE_FINAL_TYPE, and the _NamespaceObject structure would have to be declared explicitly in the .c file. In the case of a derivable object, you do not need to declare this structure; it is generated automatically when the macro expands.

We describe the structure of _AnimalCatClass. This structure exists in a single copy, it is created during the creation of the first instance of our facility, and is destroyed after the destruction of the last instance. As the first field, it should contain the same structure of the parent class, in our case GObject, since we inherit directly from it. After that, there are other fields, mainly pointers to functions that implement the functionality of virtual methods, as well as fields similar to static fields of C ++ classes.



```





# GObject: 상속과 인터페이스 


The whole cycle is about GObject:

GObject: the basics
GObject: inheritance and interfaces
GObject: encapsulation, instantiation, introspection
Inheriting from descendants of GObject
 
일반적으로 GObject 는 단일 상속만 의미한다. 다중 상속에 대해서는 자바처럼 인터페이스를 사용한다. 

Cat 을 상속하는 Tiger 타입을 생성해보자. 여기서는 Tiger 를 final object 로 만들 것이다. 따라서 Tiger 를 누군가 상속할 수 없을거다. 

```console
$ gcc *.c `pkg-config --libs --cflags glib-2.0 gobject-2.0 `


```


Referecne : https://sudonull.com/post/62697-GObject-the-basics (1편)
Reference : https://blog.emptyq.net/a?ID=00004-216412bd-5dea-41e6-87ea-835ffe6595e7(2편)
https://weekly-geekly.imtqy.com/articles/418443/index.html ( 3편 ) 

namespace BoxEngine {
namespace Editor {

	/// <summary>
	/// Interface deal with layouts states.
	/// </summary>
	class Layout
	{
	public:
		virtual void Awake() {};
		virtual void Start() {};
		virtual void Update() {};
		virtual void Destroy() {};
		virtual void Reset() {};
	};
}}
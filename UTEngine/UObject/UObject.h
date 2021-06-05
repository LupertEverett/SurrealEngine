#pragma once

#include "Package/ObjectStream.h"
#include "Math/vec.h"
#include "PropertyOffsets.h"

class UObject;
class UClass;
class UProperty;
class Package;

enum UnrealPropertyType
{
	UPT_Invalid,
	UPT_Byte,
	UPT_Int,
	UPT_Bool,
	UPT_Float,
	UPT_Object,
	UPT_Name,
	UPT_String,
	UPT_Class,
	UPT_Array,
	UPT_Struct,
	UPT_Vector,
	UPT_Rotator,
	UPT_Str,
	UPT_Map,
	UPT_FixedArray
};

enum UnrealUPropertyStruct
{
	UPS_Invalid,
	UPS_Vector,
	UPS_Matrix,
	UPS_Plane,
	UPS_Sphere,
	UPS_Scale,
	UPS_Coords,
	UPS_ModelCoords,
	UPS_Rotator,
	UPS_Box,
	UPS_Color,
	UPS_Palette,
	UPS_Mipmap,
	UPS_PointRegion
};

struct PropertyHeader
{
	UnrealPropertyType type;
	int arrayIndex = 0;
	bool boolValue = false;
	std::string structName;
	int size = 0;
};

enum UnrealSheerAxis
{
	SHEER_None = 0,
	SHEER_XY = 1,
	SHEER_XZ = 2,
	SHEER_YX = 3,
	SHEER_YZ = 4,
	SHEER_ZX = 5,
	SHEER_ZY = 6,
};

class Rotator
{
public:
	Rotator() = default;
	Rotator(int pitch, int yaw, int roll) : Pitch(pitch), Yaw(yaw), Roll(roll) { }

	int Pitch;
	int Yaw;
	int Roll;

	float PitchDegrees() const { return Pitch * (360.0f / 65536.0f); }
	float YawDegrees() const { return Yaw * (360.0f / 65536.0f); }
	float RollDegrees() const { return Roll * (360.0f / 65536.0f); }
};

inline Rotator normalize(Rotator rot)
{
	int pitch = rot.Pitch & 0xffff;
	int roll = rot.Roll & 0xffff;
	int yaw = rot.Yaw & 0xffff;
	if (pitch > 32767) pitch -= 0x10000;
	if (roll > 32767) roll -= 0x10000;
	if (yaw > 32767) yaw -= 0x10000;
	return { pitch, yaw, roll };
}

class Color
{
public:
	uint8_t R, G, B, A;
};

inline bool operator==(const Color& a, const Color& b) { return a.R == b.R && a.G == b.G && a.B == b.B && a.A == b.A; }
inline bool operator!=(const Color& a, const Color& b) { return a.R != b.R || a.G != b.G || a.B != b.B || a.A != b.A; }

inline bool operator==(const Rotator& a, const Rotator& b) { return a.Pitch == b.Pitch && a.Yaw == b.Yaw && a.Roll == b.Roll; }
inline bool operator!=(const Rotator& a, const Rotator& b) { return a.Pitch != b.Pitch || a.Yaw != b.Yaw || a.Roll != b.Roll; }

class ObjectDelayLoad
{
public:
	ObjectDelayLoad(Package* package, int index, std::string objName, UClass* cls) : package(package), Index(index), ObjName(objName), Class(cls) { }

	Package* package = nullptr;
	int Index = 0;
	std::string ObjName;
	UClass* Class = nullptr;
};

class PropertyDataBlock
{
public:
	PropertyDataBlock() = default;
	~PropertyDataBlock() { Reset(); }

	void Init(UClass* cls);
	void ReadProperties(ObjectStream* stream);

	void* Ptr(const UProperty* prop);
	void* Ptr(size_t offset) { return static_cast<uint8_t*>(Data) + offset; }
	const void* Ptr(const UProperty* prop) const;
	const void* Ptr(size_t offset) const { return static_cast<const uint8_t*>(Data) + offset; }

	template<typename T>
	T& Value(size_t offset) { return *reinterpret_cast<T*>(static_cast<uint8_t*>(Data) + offset); }

	void* Data = nullptr;
	UClass* Class = nullptr;

private:
	void Reset();

	PropertyDataBlock(const PropertyDataBlock&) = delete;
	PropertyDataBlock& operator=(const PropertyDataBlock&) = delete;
};

class UObject
{
public:
	UObject(std::string name, UClass* base, ObjectFlags flags);
	virtual ~UObject() = default;

	void LoadNow();
	virtual void Load(ObjectStream* stream);

	bool HasProperty(const std::string& name) const;
	void* GetProperty(const std::string& name);
	const void* GetProperty(const std::string& name) const;

	uint8_t GetByte(const std::string& name) const;
	uint32_t GetInt(const std::string& name) const;
	bool GetBool(const std::string& name) const;
	float GetFloat(const std::string& name) const;
	vec3 GetVector(const std::string& name) const;
	Rotator GetRotator(const std::string& name) const;
	const std::string& GetString(const std::string& name) const;
	UObject* GetUObject(const std::string& name);
	Color GetColor(const std::string& name);

	void SetByte(const std::string& name, uint8_t value);
	void SetInt(const std::string& name, uint32_t value);
	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);
	void SetVector(const std::string& name, const vec3& value);
	void SetRotator(const std::string& name, const Rotator& value);
	void SetString(const std::string& name, const std::string& value);
	void SetObject(const std::string& name, const UObject* value);

	std::unique_ptr<ObjectDelayLoad> DelayLoad;

	std::string Name;
	UClass* Base = nullptr;
	ObjectFlags Flags = ObjectFlags::None;

	PropertyDataBlock PropertyData;
	std::string StateName;

	template<typename T>
	T& Value(size_t offset) { return *static_cast<T*>(PropertyData.Ptr(offset)); }

	template<typename T>
	static T* Cast(UObject* obj)
	{
		T* target = dynamic_cast<T*>(obj);
		if (target == nullptr && obj != nullptr)
		{
			throw std::runtime_error("Could not cast object " + obj->Name + " (class " + GetUClassName(obj) + ") to " + (std::string)typeid(T).name());
		}
		return target;
	}

	template<typename T>
	static T* TryCast(UObject* obj)
	{
		return dynamic_cast<T*>(obj);
	}

	static std::string GetUClassName(UObject* obj);

	static void InitPropertyOffsets(PackageManager* packages);

	UClass*& Class() { return Value<UClass*>(PropOffsets_Object.Class); } // native
	// std::string& Name() { return Value<std::string>(PropOffsets_Object.Name); } // native
	// int& ObjectFlags() { return Value<int>(PropOffsets_Object.ObjectFlags); } // native
	int& ObjectInternal() { return Value<int>(PropOffsets_Object.ObjectInternal); } // native
	UObject*& Outer() { return Value<UObject*>(PropOffsets_Object.Outer); } // native

private:
	struct PropertyOffsets
	{
		size_t Class;
		size_t Name;
		size_t ObjectFlags;
		size_t ObjectInternal;
		size_t Outer;
	};
	static PropertyOffsets propoffsets;
};

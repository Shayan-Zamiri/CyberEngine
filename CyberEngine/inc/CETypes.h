#pragma once

#include <cstdint>
#include "TSMatrix4D.h"

namespace CE
{
	using U8 = uint8_t;
	using U16 = uint16_t;
	using U32 = uint32_t;
	using U64 = uint64_t;

	using U8_S = uint_least8_t;
	using U16_S = uint_least16_t;
	using U32_S = uint_least32_t;
	using U64_S = uint_least64_t;

	using U8_F = uint_fast8_t;
	using U16_F = uint_fast16_t;
	using U32_F = uint_fast32_t;
	using U64_F = uint_fast64_t;

	using I8 = int8_t;
	using I16 = int16_t;
	using I32 = int32_t;
	using I64 = int64_t;

	using I8_F = int_fast8_t;
	using I16_F = int_fast16_t;
	using I32_F = int_fast32_t;
	using I64_F = int_fast64_t;

	using I8_S = int_least8_t;
	using I16_S = int_least16_t;
	using I32_S = int_least32_t;
	using I64_S = int_least64_t;

	using IMAX = intmax_t;
	using UMAX = uintmax_t;

	using Matrix4D = Terathon::Matrix4D;
	using Matrix3D = Terathon::Matrix3D;
	using Matrix2D = Terathon::Matrix2D;
	using Vector4D = Terathon::Vector4D;
	using Vector3D = Terathon::Vector3D;
	using Vector2D = Terathon::Vector2D;
	using Transform4D = Terathon::Transform4D;

	// ENUMS

	enum class EDirection
	{
		FORWARD,
		RIGHT,
		BACKWARD,
		LEFT,
		UP,
		DOWN
	};

	enum class ETextureType
	{
		/** Dummy value.
		 *
		 *  No texture, but the value to be used as 'texture semantic'
		 *  (#aiMaterialProperty::mSemantic) for all material properties
		 *  *not* related to textures.
		 */
		NONE = 0,

		/** LEGACY API MATERIALS
		 * Legacy refers to materials which
		 * Were originally implemented in the specifications around 2000.
		 * These must never be removed, as most engines support them.
		 */

		/** The texture is combined with the result of the diffuse
		 *  lighting equation.
		 *  OR
		 *  PBR Specular/Glossiness
		 */
		DIFFUSE = 1,

		/** The texture is combined with the result of the specular
		 *  lighting equation.
		 *  OR
		 *  PBR Specular/Glossiness
		 */
		SPECULAR = 2,

		/** The texture is combined with the result of the ambient
		 *  lighting equation.
		 */
		AMBIENT = 3,

		/** The texture is added to the result of the lighting
		 *  calculation. It isn't influenced by incoming light.
		 */
		EMISSIVE = 4,

		/** The texture is a height map.
		 *
		 *  By convention, higher gray-scale values stand for
		 *  higher elevations from the base height.
		 */
		HEIGHT = 5,

		/** The texture is a (tangent space) normal-map.
		 *
		 *  Again, there are several conventions for tangent-space
		 *  normal maps. Assimp does (intentionally) not
		 *  distinguish here.
		 */
		NORMALS = 6,

		/** The texture defines the glossiness of the material.
		 *
		 *  The glossiness is in fact the exponent of the specular
		 *  (phong) lighting equation. Usually there is a conversion
		 *  function defined to map the linear color values in the
		 *  texture to a suitable exponent. Have fun.
		*/
		SHININESS = 7,

		/** The texture defines per-pixel opacity.
		 *
		 *  Usually 'white' means opaque and 'black' means
		 *  'transparency'. Or quite the opposite. Have fun.
		*/
		OPACITY = 8,

		/** Displacement texture
		 *
		 *  The exact purpose and format is application-dependent.
		 *  Higher color values stand for higher vertex displacements.
		*/
		DISPLACEMENT = 9,

		/** Lightmap texture (aka Ambient Occlusion)
		 *
		 *  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
		 *  covered by this material property. The texture contains a
		 *  scaling value for the final color value of a pixel. Its
		 *  intensity is not affected by incoming light.
		*/
		LIGHTMAP = 10,

		/** Reflection texture
		 *
		 * Contains the color of a perfect mirror reflection.
		 * Rarely used, almost never for real-time applications.
		*/
		REFLECTION = 11,

		/** PBR Materials
		 * PBR definitions from maya and other modelling packages now use this standard.
		 * This was originally introduced around 2012.
		 * Support for this is in game engines like Godot, Unreal or Unity3D.
		 * Modelling packages which use this are very common now.
		 */

		BASE_COLOR = 12,
		NORMAL_CAMERA = 13,
		EMISSION_COLOR = 14,
		METALNESS = 15,
		DIFFUSE_ROUGHNESS = 16,
		AMBIENT_OCCLUSION = 17,

		/** PBR Material Modifiers
		* Some modern renderers have further PBR modifiers that may be overlaid
		* on top of the 'base' PBR materials for additional realism.
		* These use multiple texture maps, so only the base type is directly defined
		*/

		/** Sheen
		* Generally used to simulate textiles that are covered in a layer of microfibers
		* eg velvet
		* https://github.com/KhronosGroup/glTF/tree/master/extensions/2.0/Khronos/KHR_materials_sheen
		*/
		SHEEN = 19,

		/** Clearcoat
		* Simulates a layer of 'polish' or 'laquer' layered on top of a PBR substrate
		* https://autodesk.github.io/standard-surface/#closures/coating
		* https://github.com/KhronosGroup/glTF/tree/master/extensions/2.0/Khronos/KHR_materials_clearcoat
		*/
		CLEARCOAT = 20,

		/** Transmission
		* Simulates transmission through the surface
		* May include further information such as wall thickness
		*/
		TRANSMISSION = 21,

		/** Unknown texture
		 *
		 *  A texture reference that does not match any of the definitions
		 *  above is considered to be 'unknown'. It is still imported,
		 *  but is excluded from any further post-processing.
		*/
		UNKNOWN = 18,
	};

	inline std::string TextureTypeToString(ETextureType pType)
	{
		switch (pType)
		{
			case ETextureType::DIFFUSE:
				return "texture_diffuse";
			case ETextureType::SPECULAR:
				return "texture_specular";
			case ETextureType::NORMALS:
				return "texture_normal";
			case ETextureType::HEIGHT:
				return "texture_height";
			default:
				return std::string{};
		}
	}
}

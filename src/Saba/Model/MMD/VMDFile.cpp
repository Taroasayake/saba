//
// Copyright(c) 2016-2017 benikabocha.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#include "VMDFile.h"

#include <Saba/Base/Log.h>
#include <Saba/Base/File.h>

namespace saba
{
	namespace
	{
		template <typename T>
		bool Read(T* val, File& file)
		{
			return file.Read(val);
		}

		bool ReadHeader(VMDFile* vmd, File& file)
		{
			Read(&vmd->m_header.m_header, file);
			Read(&vmd->m_header.m_modelName, file);

			if (vmd->m_header.m_header.ToString() != "Vocaloid Motion Data 0002" &&
				vmd->m_header.m_header.ToString() != "Vocaloid Motion Data"
				)
			{
				SABA_WARN("VMD Header error.");
				return false;
			}

			return !file.IsBad();
		}

		bool ReadMotion(VMDFile* vmd, File& file)
		{
			uint32_t motionCount = 0;
			if (!Read(&motionCount, file))
			{
				return false;
			}

			vmd->m_motions.resize(motionCount);
			for (auto& motion : vmd->m_motions)
			{
				Read(&motion.m_boneName, file);
				Read(&motion.m_frame, file);
				Read(&motion.m_translate, file);
				Read(&motion.m_quaternion, file);
				Read(&motion.m_interpolation, file);
			}

			return !file.IsBad();
		}

		bool ReadBlednShape(VMDFile* vmd, File& file)
		{
			uint32_t blendShapeCount = 0;
			if (!Read(&blendShapeCount, file))
			{
				return false;
			}

			vmd->m_morphs.resize(blendShapeCount);
			for (auto& morph : vmd->m_morphs)
			{
				Read(&morph.m_blendShapeName, file);
				Read(&morph.m_frame, file);
				Read(&morph.m_weight, file);
			}

			return !file.IsBad();
		}

		bool ReadCamera(VMDFile* vmd, File& file)
		{
			uint32_t cameraCount = 0;
			if (!Read(&cameraCount, file))
			{
				return false;
			}

			vmd->m_cameras.resize(cameraCount);
			for (auto& camera : vmd->m_cameras)
			{
				Read(&camera.m_frame, file);
				Read(&camera.m_distance, file);
				Read(&camera.m_interest, file);
				Read(&camera.m_rotate, file);
				Read(&camera.m_interpolation, file);
				Read(&camera.m_viewAngle, file);
				Read(&camera.m_isPerspective, file);
			}

			return !file.IsBad();
		}

		bool ReadLight(VMDFile* vmd, File& file)
		{
			uint32_t lightCount = 0;
			if (!Read(&lightCount, file))
			{
				return false;
			}

			vmd->m_lights.resize(lightCount);
			for (auto& light : vmd->m_lights)
			{
				Read(&light.m_frame, file);
				Read(&light.m_color, file);
				Read(&light.m_position, file);
			}

			return !file.IsBad();
		}

		bool ReadShadow(VMDFile* vmd, File& file)
		{
			uint32_t shadowCount = 0;
			if (!Read(&shadowCount, file))
			{
				return false;
			}

			vmd->m_shadows.resize(shadowCount);
			for (auto& shadow : vmd->m_shadows)
			{
				Read(&shadow.m_frame, file);
				Read(&shadow.m_shadowType, file);
				Read(&shadow.m_distance, file);
			}

			return !file.IsBad();
		}

		bool ReadIK(VMDFile* vmd, File& file)
		{
			uint32_t ikCount = 0;
			if (!Read(&ikCount, file))
			{
				return false;
			}

			vmd->m_iks.resize(ikCount);
			for (auto& ik : vmd->m_iks)
			{
				Read(&ik.m_frame, file);
				Read(&ik.m_show, file);
				uint32_t ikInfoCount = 0;
				if (!Read(&ikInfoCount, file))
				{
					return false;
				}
				ik.m_ikInfos.resize(ikInfoCount);
				for (auto& ikInfo : ik.m_ikInfos)
				{
					Read(&ikInfo.m_name, file);
					Read(&ikInfo.m_enable, file);
				}
			}

			return !file.IsBad();
		}

		bool ReadVMDFile(VMDFile* vmd, File& file)
		{
			if (!ReadHeader(vmd, file))
			{
				SABA_WARN("ReadHeader Fail.");
				return false;
			}

			if (!ReadMotion(vmd, file))
			{
				SABA_WARN("ReadMotion Fail.");
				return false;
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadBlednShape(vmd, file))
				{
					SABA_WARN("ReadBlednShape Fail.");
					return false;
				}
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadCamera(vmd, file))
				{
					SABA_WARN("ReadCamera Fail.");
					return false;
				}
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadLight(vmd, file))
				{
					SABA_WARN("ReadLight Fail.");
					return false;
				}
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadShadow(vmd, file))
				{
					SABA_WARN("ReadShadow Fail.");
					return false;
				}
			}

			if (file.Tell() < file.GetSize())
			{
				if (!ReadIK(vmd, file))
				{
					SABA_WARN("ReadIK Fail.");
					return false;
				}
			}

			return true;
		}
	}

#include <stdlib.h>
	void Dump(VMDFile* vmd, const char* filename)
	{
		char dumpfilename[512];

		// Dump用のファイルを用意する
		{
			char drive[5];
			char dir[256];
			char fname[256];
			char ext[256];

			errno_t e = _splitpath_s(filename, drive, sizeof(drive), dir, sizeof(dir), fname, sizeof(fname), ext, sizeof(ext));

			e = _makepath_s(dumpfilename, sizeof(dumpfilename), drive, dir, fname, ".txt");
		}

		File file;
		bool result = file.OpenFile(dumpfilename, "wt, ccs=UTF-8");
		if (result)
		{
			fwprintf(file.m_fp, L"%s\n", ToWString(vmd->m_header.m_header.ToUtf8String()).c_str());
			fwprintf(file.m_fp, L"%s\n", ToWString(vmd->m_header.m_modelName.ToUtf8String()).c_str());
			fwprintf(file.m_fp, L"\n");

			fwprintf(file.m_fp, L"モーションデータ数:%zd\n", vmd->m_motions.size());
			{
				int c = 0;
				for (auto& motion : vmd->m_motions)
				{
					fwprintf(file.m_fp, L"%06d", c);
					fwprintf(file.m_fp, L":ボーン名:%s", ToWString(motion.m_boneName.ToUtf8String()).c_str());
					fwprintf(file.m_fp, L":frame:%d", motion.m_frame);
					fwprintf(file.m_fp, L":translate(%f,%f,%f)", motion.m_translate.x, motion.m_translate.y, motion.m_translate.z);
					//fwprintf(file.m_fp, L":quaternion(%f,%f,%f)", motion.m_quaternion.);


					fwprintf(file.m_fp, L"\n");
					++c;
				}
			}
			fwprintf(file.m_fp, L"\n");


		}
		file.Close();
	}

	bool ReadVMDFile(VMDFile * vmd, const char * filename)
	{
		File file;
		if (!file.Open(filename))
		{
			SABA_WARN("VMD File Open Fail. {}", filename);
			return false;
		}

		bool result = ReadVMDFile(vmd, file);

		if (result)
		{
			Dump(vmd, filename);
		}

		return result;
	}

}

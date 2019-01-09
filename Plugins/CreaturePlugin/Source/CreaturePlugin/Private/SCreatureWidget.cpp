#include "CreaturePluginPCH.h"
#include "SCreatureWidget.h"
#include "Slate/SMeshWidget.h"
#include "Rendering/DrawElements.h"
#include "Modules/ModuleManager.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Framework/Application/SlateApplication.h"
#include "CustomProceduralMeshComponent.h"
#include "CreatureCore.h"

#include "SlateMaterialBrush.h"
#include "Runtime/SlateRHIRenderer/Public/Interfaces/ISlateRHIRendererModule.h"
#include "Slate/SlateVectorArtData.h"
#include "Slate/SlateVectorArtInstanceData.h"

void SCreatureWidget::Construct(const FArguments& Args)
{

}

void SCreatureWidget::SetCreatureCore(CreatureCore * creature_core_in)
{
	creature_core = creature_core_in;
}

void SCreatureWidget::SetBrush(FSlateBrush * render_brush_in)
{
	render_brush = render_brush_in;
}

void SCreatureWidget::UpdateMesh(const FVector2D& translation, const FVector2D& local_scale)
{
	if (creature_core == nullptr)
	{
		return;
	}

	auto proc_mesh = creature_core->GetProcMeshData(world_type);

	// Update Indices
	if (render_data.IndexData.Num() != proc_mesh.indices_num) {
		render_data.IndexData.SetNumUninitialized(proc_mesh.indices_num);
	}

	for (int i = 0; i < proc_mesh.indices_num; i++)
	{
		render_data.IndexData[i] = static_cast<SlateIndex>(proc_mesh.indices[i]);
	}

	// Update Vertex Data
	if (render_data.VertexData.Num() != proc_mesh.point_num) {
		render_data.VertexData.SetNumUninitialized(proc_mesh.point_num);
	}

	for (int i = 0; i < proc_mesh.point_num; i++)
	{
		FSlateVertex& new_vert = render_data.VertexData[i];
		
		new_vert.Position.X = proc_mesh.points[i * 3];
		new_vert.Position.Y = proc_mesh.points[i * 3 + 1];
		new_vert.Position.X *= mesh_scale.X * local_scale.X;
		new_vert.Position.Y *= -mesh_scale.Y * local_scale.Y;
		new_vert.Position += translation;

		uint8 cur_alpha = (*proc_mesh.region_alphas)[i];
		new_vert.Color = FColor(cur_alpha, cur_alpha, cur_alpha, cur_alpha);

		float cur_u = proc_mesh.uvs[i * 2];
		float cur_v = proc_mesh.uvs[i * 2 + 1];
		new_vert.TexCoords[0] = cur_u;
		new_vert.TexCoords[1] = cur_v;
		new_vert.TexCoords[2] = cur_u;
		new_vert.TexCoords[3] = cur_v;
		new_vert.MaterialTexCoords[0] = cur_u;
		new_vert.MaterialTexCoords[1] = cur_v;
	}
}

int32 SCreatureWidget::OnPaint(
    const FPaintArgs& Args, 
    const FGeometry& AllottedGeometry,
    const FSlateRect& MyClippingRect, 
    FSlateWindowElementList& OutDrawElements, 
    int32 LayerId, 
    const FWidgetStyle& InWidgetStyle,
    bool bParentEnabled) const
{
	const_cast<SCreatureWidget *>(this)->UpdateMesh(
		AllottedGeometry.AbsolutePosition + (AllottedGeometry.GetAbsoluteSize() * 0.5f),
		AllottedGeometry.GetAbsoluteSize() * 0.02f);
	auto can_draw = render_brush && (render_data.VertexData.Num() > 0) && (render_data.IndexData.Num() > 0);
	if (can_draw)
	{
		FSlateBrush * MyBrush = render_brush;
		FSlateShaderResourceProxy* ResourceProxy = FSlateDataPayload::ResourceManager->GetShaderResource(*MyBrush);
		FSlateResourceHandle Handle = FSlateApplication::Get().GetRenderer()->GetResourceHandle(*MyBrush);

		if (ResourceProxy) {
			FSlateDrawElement::MakeCustomVerts(
				OutDrawElements,
				LayerId,
				Handle,
				render_data.VertexData,
				render_data.IndexData,
				nullptr,
				0,
				0);
		}
	}

    return LayerId;
}


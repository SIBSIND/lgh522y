/*                                                                             
  
                                                            
  
                                                                             */

/*
 * Copyright (C) 2000 - 2013, Intel Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 */

#include <acpi/acpi.h>
#include "accommon.h"
#include "acdispat.h"
#include "acinterp.h"
#include "acnamesp.h"

#define _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exresnte")

/*                                                                              
  
                                             
  
                                                                     
                                                                            
                                                                 
                                                                            
                                                                          
  
                      
  
                                                           
  
                                                                     
                                                                             
                                                
  
                         
                        
                        
                       
                         
  
                                                                              */
acpi_status
acpi_ex_resolve_node_to_value(struct acpi_namespace_node **object_ptr,
			      struct acpi_walk_state *walk_state)
{
	acpi_status status = AE_OK;
	union acpi_operand_object *source_desc;
	union acpi_operand_object *obj_desc = NULL;
	struct acpi_namespace_node *node;
	acpi_object_type entry_type;

	ACPI_FUNCTION_TRACE(ex_resolve_node_to_value);

	/*
                                                                            
                                        
  */
	node = *object_ptr;
	source_desc = acpi_ns_get_attached_object(node);
	entry_type = acpi_ns_get_type((acpi_handle) node);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Entry=%p SourceDesc=%p [%s]\n",
			  node, source_desc,
			  acpi_ut_get_type_name(entry_type)));

	if ((entry_type == ACPI_TYPE_LOCAL_ALIAS) ||
	    (entry_type == ACPI_TYPE_LOCAL_METHOD_ALIAS)) {

		/*                                                  */

		node = ACPI_CAST_PTR(struct acpi_namespace_node, node->object);
		source_desc = acpi_ns_get_attached_object(node);
		entry_type = acpi_ns_get_type((acpi_handle) node);
		*object_ptr = node;
	}

	/*
                                                       
                                                                            
                                                     
                                                                      
  */
	if ((entry_type == ACPI_TYPE_DEVICE) ||
	    (entry_type == ACPI_TYPE_THERMAL) ||
	    (entry_type == ACPI_TYPE_METHOD) ||
	    (node->flags & (ANOBJ_METHOD_ARG | ANOBJ_METHOD_LOCAL))) {
		return_ACPI_STATUS(AE_OK);
	}

	if (!source_desc) {
		ACPI_ERROR((AE_INFO, "No object attached to node %p", node));
		return_ACPI_STATUS(AE_AML_NO_OPERAND);
	}

	/*
                                                                     
                                     
  */
	switch (entry_type) {
	case ACPI_TYPE_PACKAGE:

		if (source_desc->common.type != ACPI_TYPE_PACKAGE) {
			ACPI_ERROR((AE_INFO, "Object not a Package, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		status = acpi_ds_get_package_arguments(source_desc);
		if (ACPI_SUCCESS(status)) {

			/*                                              */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
		}
		break;

	case ACPI_TYPE_BUFFER:

		if (source_desc->common.type != ACPI_TYPE_BUFFER) {
			ACPI_ERROR((AE_INFO, "Object not a Buffer, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		status = acpi_ds_get_buffer_arguments(source_desc);
		if (ACPI_SUCCESS(status)) {

			/*                                              */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
		}
		break;

	case ACPI_TYPE_STRING:

		if (source_desc->common.type != ACPI_TYPE_STRING) {
			ACPI_ERROR((AE_INFO, "Object not a String, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/*                                              */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		break;

	case ACPI_TYPE_INTEGER:

		if (source_desc->common.type != ACPI_TYPE_INTEGER) {
			ACPI_ERROR((AE_INFO, "Object not a Integer, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}

		/*                                              */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		break;

	case ACPI_TYPE_BUFFER_FIELD:
	case ACPI_TYPE_LOCAL_REGION_FIELD:
	case ACPI_TYPE_LOCAL_BANK_FIELD:
	case ACPI_TYPE_LOCAL_INDEX_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "FieldRead Node=%p SourceDesc=%p Type=%X\n",
				  node, source_desc, entry_type));

		status =
		    acpi_ex_read_data_from_field(walk_state, source_desc,
						 &obj_desc);
		break;

		/*                                                                */

	case ACPI_TYPE_MUTEX:
	case ACPI_TYPE_POWER:
	case ACPI_TYPE_PROCESSOR:
	case ACPI_TYPE_EVENT:
	case ACPI_TYPE_REGION:

		/*                                              */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		break;

		/*                                                                     */

	case ACPI_TYPE_ANY:

		ACPI_ERROR((AE_INFO,
			    "Untyped entry %p, no attached object!", node));

		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);	/*                   */

	case ACPI_TYPE_LOCAL_REFERENCE:

		switch (source_desc->reference.class) {
		case ACPI_REFCLASS_TABLE:	/*                      */
		case ACPI_REFCLASS_REFOF:
		case ACPI_REFCLASS_INDEX:

			/*                                              */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
			break;

		default:
			/*                                      */

			ACPI_ERROR((AE_INFO,
				    "Unsupported Reference type 0x%X",
				    source_desc->reference.class));

			return_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		}
		break;

	default:

		/*                                   */

		ACPI_ERROR((AE_INFO,
			    "Node %p - Unknown object type 0x%X",
			    node, entry_type));

		return_ACPI_STATUS(AE_AML_OPERAND_TYPE);

	}			/*                     */

	/*                              */

	*object_ptr = (void *)obj_desc;
	return_ACPI_STATUS(status);
}
